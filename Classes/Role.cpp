#include "Role.h"
#include "DefaultData.h"
#include "Bullet.h"
#include "EffectUtil.h"
Role::Role():m_controlable(false),m_arm(nullptr),m_trace(nullptr),m_isHL(false),
	m_attackTarget(nullptr),m_attackTargetPtr(nullptr),m_hpSlider(nullptr)
{
	m_arm_offsetX = m_arm_offsetY = 0;
	m_atkHateValue = HERO_ATK_HATE_VALUE;

	m_id = getUniqueId();
	
	en_stat = ROLE_NULL;
	m_type = ROLE_TYPE_NULL;
	
	m_speed = m_initSpeed =ROLE_DEFAULT_SPEED;
	
	m_attackDistance = m_initAttackDistance = ROLE_DEFAULT_ATK_DIS;

	m_hp = m_initHp = ROLE_DEFAULT_HP;

	m_atk = m_initAtk =  ROLE_DEFAULT_ATK;

	m_defence = m_initDefence = ROLE_DEFAULT_DEF;
	
	m_atkSpeed = m_initAtkSpeed = ROLE_DEFAULT_ATK_SPEED;
	
	m_bulletImg = "bullet_NULL.png";

	m_isNaima = false;

	m_bulletSpeed = m_initBulletSpeed = ROLE_DEFAULT_BULLET_SPEED;
}

Role* Role::create(const std::string& name,FlightLayer* layer){
	Role* ret = new Role();
	if(ret && ret->init(name,layer)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool Role::init(const std::string& name,FlightLayer* layer){
	m_layer = layer;
	if(!m_arm){
		m_arm = Armature::create(name);
		m_arm->setPosition(m_arm_offsetX,m_arm_offsetY);
		m_arm->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Role::onBondAnimationFinish,this));
		m_defalutColor = m_arm->getColor();
		setContentSize(m_arm->getContentSize());
		this->addChild(m_arm,1);
		
		m_armFaceTo = true;

		scheduleUpdate();

		initHpSlider();

		m_selectCircle = Sprite::create("selectCircle.png");
		m_selectCircle->setVisible(false);
		m_selectCircle->setPosition(0,15);
		this->addChild(m_selectCircle);

		return true;
	}else{
		return false;
	}
}

void Role::initHpSlider(){
	m_hpSlider = ControlSlider::create("bloodbg.png","blood.png","sliderThumb.png");
	m_hpSlider->setTouchEnabled(false);
	m_hpSlider->setMaximumValue(m_initHp);
	m_hpSlider->setMinimumValue(0);
	m_hpSlider->setValue(m_hp);
	m_hpSlider->setPosition(getHpSliderPos());
	this->addChild(m_hpSlider);
}

Point Role::getHpSliderPos(){
	return Point(0,0);
}


void Role::onBondAnimationFinish(Armature* arm,MovementEventType type,const std::string& name){
	if(type == COMPLETE){
		if(name == "hit"){
			CCLOG("HIT COMPLETE");
			en_stat = ROLE_STAND;
		}
		if(name == "attack"){
			CCLOG("ATTACK COMPLETE");
			//恢复速度
			m_speed = m_initSpeed;
			m_arm->getAnimation()->setSpeedScale(1.0f);
			this->stand();
		}
	}
	if(type == START){
		if(name == "attack"){
			CCLOG("SEND BULLET");
			sendBullet();
		}
	}
}

void Role::setControlable(bool b){
	m_controlable = b;
}

void Role::setAttackTarget(Role** targetPtr){
	m_attackTargetPtr = targetPtr;
	if(targetPtr){
		m_attackTarget = *m_attackTargetPtr;
	}else{
		m_attackTarget = nullptr;
	}
}

Rect Role::getBoundingBox(){
	Size heroSize = m_arm->getContentSize();
	Rect heroRect(this->getPositionX()- heroSize.width/4,this->getPositionY(),heroSize.width/2,heroSize.height); 
	return heroRect;
}

void Role::setHeightLight(bool b){
	m_isHL = b;
}

void Role::setEndPoint(const Point& p){
	m_endPoint = p;
}

Point Role::getEndPoint(){
	return m_endPoint;
}

bool Role::onTouchBegan(Touch* touch,Event* event){
	if(!m_controlable){
		return false;
	}
	if(m_arm){
		Point point = touch->getLocationInView();
		point = Director::getInstance()->convertToGL(point);
		m_endPoint = point;

		CCLOG("TOUCH POINT PX = %f,PY = %f",point.x,point.y);
		
		Rect heroRect = getBoundingBox();

		if(heroRect.containsPoint(point)){
			m_trace = Sprite::create("color.png");		
			m_trace->setAnchorPoint(Point(0,0.5f));
			this->addChild(m_trace,0);
			CCLOG("CLICK MY HERO");
			setHeightLight(true);
			return true;
		}else{
			CCLOG("NOT CONTAIN");
			return false;
		}
	}
	return false;
}

void Role::onTouchMoved(Touch* touch,Event* event){
	Point point = touch->getLocationInView();
	point = Director::getInstance()->convertToGL(point);
	m_endPoint = point;
	
}

void Role::onTouchEnded(Touch* touch,Event* event){
	if(m_trace){
		m_trace->removeFromParentAndCleanup(true);
		m_trace = nullptr;
		setHeightLight(false);
	}
}

void Role::update_attackTarget(){
	if(m_attackTargetPtr){
		m_attackTarget = *m_attackTargetPtr;		
	}else{
		m_attackTarget = nullptr;
	}
}

void Role::update_trace(){
	if(m_trace){
		if(getBoundingBox().containsPoint(m_endPoint)){
			m_endPoint = this->getPosition();
		}
		Point begin(CCDirector::getInstance()->convertToGL(this->getPosition()));
		Point end(CCDirector::getInstance()->convertToGL(m_endPoint));
		m_trace->setRotation(CC_RADIANS_TO_DEGREES(ccpToAngle(end - begin)));
		m_trace->setScaleX(ccpDistance(begin,end)/m_trace->getContentSize().width);
	}
}

void Role::update_checkHL(){
	if(m_isHL){
		m_arm->setColor(Color3B(199,243,62));
		m_selectCircle->setVisible(true);
	}else{
		m_arm->setColor(m_defalutColor);
		m_selectCircle->setVisible(false);
	}
}

void Role::update_pos(){
	if(en_stat == ROLE_ATTACK){
		//如果是攻击状态 位置属性不需改变
		return;
	}
	if(m_attackTarget){
		m_desPoint.y = m_attackTarget->getPositionY();
		m_desPoint.x = m_attackTarget->getPositionX();
	}
	if(m_attackTarget){
		if(m_attackTarget->getPositionX() > getPositionX()){
			m_armFaceTo = false;
		}else{
			m_armFaceTo = true;
		}
		if(m_armFaceTo){
			m_arm->setVisible(false);
			m_arm->setPosition(m_arm_offsetX,m_arm_offsetY);
			m_arm->setScaleX(1.0f);
			m_arm->setVisible(true);
		}else{
			m_arm->setVisible(false);
			m_arm->setScaleX(-1.0f);
			m_arm->setPosition(-m_arm_offsetX,m_arm_offsetY);
			m_arm->setVisible(true);
		}
		if(!Rect(getPositionX()-m_attackDistance,getPositionY()-m_attackDistance,2*m_attackDistance,2*m_attackDistance).containsPoint(m_desPoint)){
			this->move();
			float distance = ccpDistance(getPosition(),m_desPoint);
			float t = distance / m_speed;
			float speed_x = (m_desPoint.x - getPositionX()) / t;
			float speed_y = (m_desPoint.y - getPositionY()) / t;

			setPositionX(getPositionX() + speed_x);
			setPositionY(getPositionY() + speed_y);
		}else{
			this->attack();
			//this->setDesPoint(getPosition());
		}
	}else{
		if(m_desPoint.x > this->getPosition().x && m_armFaceTo == true){	
			m_armFaceTo = false;
		}
		if(m_desPoint.x < this->getPosition().x && m_armFaceTo == false){
			m_armFaceTo = true;
		}
		if(m_armFaceTo){
			m_arm->setVisible(false);
			m_arm->setPosition(m_arm_offsetX,m_arm_offsetY);
			m_arm->setScaleX(1.0f);
			m_arm->setVisible(true);
		}else{
			m_arm->setVisible(false);
			m_arm->setScaleX(-1.0f);
			m_arm->setPosition(-m_arm_offsetX,m_arm_offsetY);
			m_arm->setVisible(true);
		}
		if(!Rect(m_desPoint.x-m_speed/2,m_desPoint.y-m_speed/2,m_speed,m_speed).containsPoint(getPosition())){
			this->move();
			float distance = ccpDistance(getPosition(),m_desPoint);
			float t = distance / m_speed;
			float speed_x = (m_desPoint.x - getPositionX()) / t;
			float speed_y = (m_desPoint.y - getPositionY()) / t;
			setPositionX(getPositionX() + speed_x);
			setPositionY(getPositionY() + speed_y);
		}else{
			this->stand();
		}
	}
	
}

void Role::update_hp(){
	if(m_hpSlider){
		m_hpSlider->setValue(m_hp);
		m_hpSlider->setPosition(getHpSliderPos());
	}
}

void Role::update(float delta){
	update_attackTarget();
	update_trace();
	update_checkHL();
	update_pos();
	update_hp();
}

void Role::stand(){
	if(en_stat == ROLE_INJURED){
		return;
	}
	if(m_arm && en_stat!=ROLE_STAND){
		m_arm->getAnimation()->play("stand");
		CCLOG("id=%d:stand",m_id);
		en_stat = ROLE_STAND;
	}
}
void Role::move(){
	if(en_stat == ROLE_ATTACK){
		return;
	}
	if(m_arm && en_stat!=ROLE_MOVE){
		en_stat = ROLE_MOVE;
		m_arm->getAnimation()->play("walk");
		CCLOG("id=%d:move",m_id);
		CCLOG("move");
	}
}
void Role::attack(){
	if(en_stat == ROLE_INJURED)
		return;
	if(m_arm && en_stat!=ROLE_ATTACK){
		en_stat = ROLE_ATTACK;
		//攻击过程中速度为O
		m_speed = 0;
		m_arm->getAnimation()->setSpeedScale(m_atkSpeed);
		m_arm->getAnimation()->play("attack");
		this->setDesPoint(getPosition());
		CCLOG("id=%d send a hitOnMessage to id=%d",m_id,m_attackTarget->getId());
	}
}
void Role::skill(){
	
}
void Role::injured(int effect,int damage){
	runSkillEffect(effect);
	if(damage < 0){
		m_hp -= damage;
	}else{
		int real_damage = (damage-m_defence > 0)?damage - m_defence : 1;
		m_hp-= real_damage;
	}
	if(m_hp > m_initHp){
		m_hp = m_initHp;
	}
	if(m_hp <= 0){
		die();
		return;
	}
	if(en_stat == ROLE_MOVE){
		return;
	}
	MoveBy* toR = MoveBy::create(0.2f,Vec2(10,0));
	MoveBy* toL = MoveBy::create(0.2f,Vec2(-10,0));
	Sequence* seq;
	if(m_armFaceTo){
		seq = Sequence::create(toR,toL,NULL);
	}else{
		seq = Sequence::create(toL,toR,NULL);
	}
	m_arm->runAction(seq);
}

void Role::die(){
	en_stat = ROLE_DIE;
}

void Role::setBulletImg(string img){
	m_bulletImg = img;
}

string Role::getBulletImg(){
	return m_bulletImg;
}

void Role::sendBullet(){
	if(m_attackTarget && m_layer){
		m_layer->addBullet(this,m_attackTargetPtr);
	}
}

void Role::runSkillEffect(int id,int loop){
	Sprite* sp = Sprite::create("Skill/null.png");
	sp->setAnchorPoint(Point(0.5f,0));
	sp->setPosition(0,0);
	this->addChild(sp,10);
	Animate* animate = EffectUtil::getInstance()->getSkillEffectById(id,loop);
	CallFunc* call = CallFunc::create([=](){sp->removeFromParentAndCleanup(true);});
	Sequence* action = Sequence::create(animate,call,NULL);
	sp->runAction(action);
}