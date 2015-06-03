#include "FlightLayer.h"
#include "Role.h"
#include "Monster.h"
#include "Hero.h"
#include "PauseScene.h"

bool FlightLayer::init(){
	this->scheduleUpdate();
	initListener();
	m_cur_controlPtr = nullptr;
	m_cur_control = nullptr;
	m_skill = nullptr;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* BG = Sprite::create("flightBG.jpg");
	BG->setAnchorPoint(Point(0.5f,0.5f));
	BG->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(BG);
	
	MenuItemImage* pauseBtnItem = MenuItemImage::create("UI/pauseBtn.png","UI/pauseBtn.png",[=](Ref* pSender){Director::getInstance()->pushScene(PauseScene::create());});
	Menu* pauseBtn = Menu::create(pauseBtnItem,NULL);
	pauseBtn->setPosition(1180,650);
	this->addChild(pauseBtn,4);

	m_skill = nullptr;
	

	return true;
}

void FlightLayer::initTeam(const HeroMessage& h1,const HeroMessage& h2,const HeroMessage& h3){

	Hero* hero1 = Hero::create(h1.r_name,this);
	hero1->setPosition(-100,380);
	hero1->setDesPoint(Point(200,380));
	hero1->initWithMessage(h1);
	this->addRole(hero1);

	Hero* hero2 = Hero::create(h2.r_name,this);
	hero2->setPosition(-100,260);
	hero2->setDesPoint(Point(400,260));
	hero2->initWithMessage(h2);
	this->addRole(hero2);

	Hero* hero3 = Hero::create(h3.r_name,this);
	hero3->setPosition(-100,140);
	hero3->setDesPoint(Point(200,140));
	hero3->initWithMessage(h3);
	this->addRole(hero3);

}


void FlightLayer::initMonsterDeq(deque<MonsterMessage> deq){
	this->m_monsterDeq = deq;
}


void FlightLayer::addRole(Role* r){
	//r->setDesPoint(r->getPosition());
	this->addChild(r);
	Role_Ptr temp = (Role_Ptr)malloc(sizeof(Role*));
	*temp = r;
	m_rolesArray.push_back(temp);
}

void FlightLayer::initListener(){
	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(FlightLayer::onTouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(FlightLayer::onTouchMoved,this);
	touchListener->onTouchEnded = CC_CALLBACK_2(FlightLayer::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
}

bool FlightLayer::comparePosY(Role_Ptr a,Role_Ptr b){
	return ((*a)->getPositionY() < (*b)->getPositionY());
}


void FlightLayer::cleanNullPtrInArray(){
	auto it = m_rolesArray.begin();
	while(it != m_rolesArray.end()){
		if((**it)->getRoleStat() == Role::ROLE_DIE){
			(**it)->removeFromParentAndCleanup(true);
			**it = nullptr;
			it = m_rolesArray.erase(it);
		}else{
			++it;
		}
	}
}

void FlightLayer::refreshLocalZOrder(){;

	int max_z_order = m_rolesArray.size();
	if(max_z_order <= 1){
		return;
	}

	//sort(m_rolesArray.begin(),m_rolesArray.end(),bind(&FlightLayer::comparePosY,this,std::placeholders::_1,std::placeholders::_2));

	m_rolesArray.sort(bind(&FlightLayer::comparePosY,this,std::placeholders::_1,std::placeholders::_2));
	
	for(auto it = m_rolesArray.begin();it!=m_rolesArray.end();it++){
		(**it)->setLocalZOrder(max_z_order--);
	}
}

void FlightLayer::updateMyControl(){
	if(m_cur_controlPtr){
		m_cur_control = *m_cur_controlPtr;
		if(m_cur_control)
			m_cur_control->setHeightLight(true);
	}
}

void FlightLayer::updateSkill(){
	if(m_cur_control==nullptr){
		if(m_skill){
			m_skill->removeFromParentAndCleanup(true);
			m_skill = nullptr;
		}
	}
	if(m_skill == nullptr){
		if(m_cur_control){
			Hero* h = dynamic_cast<Hero*>(m_cur_control);
			m_skill = Skill::create(h);
			m_skill->setPosition(50,650);
			addChild(m_skill,4);
		}
	}else{
		if(m_cur_control){
			if(m_cur_control != m_skill->getHero()){
				m_skill->removeFromParentAndCleanup(true);
				m_skill = nullptr;
			}
		}
	}
}

void FlightLayer::updateMonster(){
	int count = 0;
	for(auto it=m_rolesArray.begin();it!=m_rolesArray.end();++it){
		if((**it)->getRoleType() == Role::ROLE_TYPE_MONSTER){
			++count;
		}
	}
	if(count < 4){
		if(m_monsterDeq.size() == 0){
			return;
		}
		MonsterMessage msg = *m_monsterDeq.begin();
		m_monsterDeq.pop_front();
		Monster* monster = Monster::create(msg.r_name,this);
		monster->initWithMessage(msg);

		monster->setPosition(2000,260);
		this->addRole(monster);
		CCLOG("ADD MONSTER:%s TO LAYER",msg.name.c_str());
	}
	return;
}

bool FlightLayer::onTouchBegan(Touch* touch,Event* event){
	if(m_rolesArray.size() < 1){
		return false;
	}
	for(auto it = m_rolesArray.begin();it!=m_rolesArray.end();++it){
		if((**it)->onTouchBegan(touch,event)){
			m_cur_controlPtr = *it;
			m_cur_control = **it;
			return true;
		}
	}
	if(m_cur_control){
		m_cur_control->setHeightLight(false);
	}
	m_cur_controlPtr = nullptr;
	return false;
}

void FlightLayer::onTouchMoved(Touch* touch,Event* event){
	if(m_cur_control){
		m_cur_control->onTouchMoved(touch,event);
	}else{
		return;
	}

	Point endPoint = touch->getLocationInView();
	endPoint = Director::getInstance()->convertToGL(endPoint);
	
	for(auto it = m_rolesArray.begin();it!=m_rolesArray.end();++it){
		if(**it == m_cur_control){
			continue;
		}
		(**it)->setHeightLight(false);
	}
	for(auto it = m_rolesArray.begin();it!=m_rolesArray.end();++it){
		if((**it)->getBoundingBox().containsPoint(endPoint)){
			if((**it)->getRoleType() == Role::ROLE_TYPE_HERO && !m_cur_control->isNaima()){
				continue;
			}
			if((**it)->getRoleType() == Role::ROLE_TYPE_MONSTER && m_cur_control->isNaima()){
				continue;
			}
			(**it)->setHeightLight(true);
			m_cur_control->setEndPoint((**it)->getPosition());
			break;
		}
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(endPoint.y > visibleSize.height - 200){
		m_cur_control->setEndPoint(Point(endPoint.x,visibleSize.height - 250));
	}
	
}

void FlightLayer::onTouchEnded(Touch* touch,Event* event){
	if(m_cur_control){
		m_cur_control->onTouchEnded(touch,event);
		Point tp = Director::getInstance()->convertToGL(touch->getLocationInView());
		if(!m_cur_control->getBoundingBox().containsPoint(tp)){
			m_cur_control->setDesPoint(m_cur_control->getEndPoint());
		}
		Role_Ptr temp = m_cur_control->getAttackTarget();//原来的攻击面具吧

		for(auto it = m_rolesArray.begin();it!=m_rolesArray.end();++it){
			if((**it)->getBoundingBox().containsPoint(tp)){
				//攻击原来的人
				if(**it == m_cur_control){
					m_cur_control->setAttackTarget(temp);
					break;
				}
				if(m_cur_control->getRoleType() == (**it)->getRoleType()){
					if(m_cur_control->isNaima()){
						m_cur_control->setAttackTarget(*it);
						break;
					}else{
						m_cur_control->setAttackTarget(nullptr);
						continue;
					}
				}else{
					if(m_cur_control->isNaima()) continue;//奶妈不能攻击怪物
					m_cur_control->setAttackTarget((*it));
					break;
				}
			}else{
				m_cur_control->setAttackTarget(nullptr);
			}
		}
	}
	for(auto it = m_rolesArray.begin();it!=m_rolesArray.end();++it){
		(**it)->setHeightLight(false);
	}
}

void FlightLayer::update(float delta){
	cleanNullPtrInArray();
	updateMyControl();
	refreshLocalZOrder();
	updateMonster();
	updateSkill();
}

void FlightLayer::addBullet(Role* sender,Role_Ptr targetPtr){
	Bullet* bullet = Bullet::createWithTarget(sender,targetPtr);
	
	this->addChild(bullet);
}