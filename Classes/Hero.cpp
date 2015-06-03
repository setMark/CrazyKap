#include "Hero.h"
#include "SkillMessageUtil.h"
#include "EffectUtil.h"
#include "SkillImpl.h"
Hero* Hero::create(const std::string& name,FlightLayer* layer){
	Hero* ret = new Hero();
	if(ret && ret->init(name,layer)){
		ret->initHero();
		ret->autorelease();
		return ret;
	}else{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

Hero* Hero::create(const std::string& name,FlightLayer* layer,int offsetX,int offsetY){
	Hero* ret = new Hero();
	if(ret && ret->init(name,layer)){
		ret->initHero();
		ret->autorelease();
		ret->setArmOffsetX(offsetX);
		ret->setArmOffsetY(offsetY);
		return ret;
	}else{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

void Hero::initHero(){
	setControlable(true);
	m_type = Role::ROLE_TYPE_HERO;
	m_state_sprite = nullptr;
	canUseSkill = true;
	skilling = false;
	m_state_lastTime = 0;
	skillCD = 0;
}

void Hero::initWithMessage(const HeroMessage& msg){
	m_hp = m_initHp = msg.hp;
	m_atk = m_initAtk = msg.atk;
	m_defence = m_initDefence = msg.def;
	m_speed = m_initSpeed = msg.speed;
	m_atkSpeed = m_initAtkSpeed = msg.atk_speed;
	m_attackDistance = m_initAttackDistance = msg.atk_dis;
	m_bulletImg = msg.bullet;
	
	m_arm_offsetX = msg.offset_x;
	m_arm_offsetY = msg.offset_y;

	m_isNaima = msg.naima;
	if(m_isNaima){
		m_initAtk = -m_initAtk;
		m_atk = -m_atk;
	}

	m_skill = SkillMessageUtil::getInstance()->getMessageById(msg.skill);
}

void Hero::skill(){
	runSkillEffect(m_skill.begin_e);
	runStateEffect(m_skill.state_e);
	skilling = true;
	canUseSkill = false;
	m_state_lastTime = 0;
	
	skillCD = m_skill.cd;

	SkillImpl impl;
	impl.runSkill(m_skill.id,this);
}

void Hero::recover(){
	m_atk = m_initAtk;
	m_attackDistance = m_initAttackDistance;
	m_defence = m_initDefence;
	m_speed = m_initSpeed;
	m_atkSpeed = m_initAtkSpeed;
	m_bulletSpeed = m_initBulletSpeed;
}

void Hero::update(float dt){
	Role::update(dt);
	update_state(dt);
	update_skill_cd(dt);
}

void Hero::update_state(float dt){
	m_state_lastTime += dt;
	if(m_state_lastTime > m_skill.lastTime){
		if(skilling){
			m_state_sprite->removeFromParentAndCleanup(true);
			m_state_sprite = nullptr;
			recover();
		}
		skilling = false;
		m_state_lastTime = 0;
	}
}

void Hero::update_skill_cd(float dt){

	if(skillCD <= 0){
		canUseSkill = true;
		skillCD = 0;
	}else{
		skillCD -= dt;
	}
}
Point Hero::getHpSliderPos(){
	return Point(0,210);
}

void Hero::runStateEffect(int id){
	if(m_state_sprite == nullptr){
		m_state_sprite = Sprite::create("Skill/null.png");
		m_state_sprite->setAnchorPoint(Point(0.5f,0));
		this->addChild(m_state_sprite,10);
	}

	Animate* a = EffectUtil::getInstance()->getSkillEffectById(id,-1);
	m_state_sprite->runAction(a);
	
}