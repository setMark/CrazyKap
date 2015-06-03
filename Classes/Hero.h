#ifndef _HERO_H_
#define _HERO_H_
#include "Role.h"
#include "cocos2d.h"
#include "HeroMessage.h"
#include "SkillMessage.h"

using namespace cocos2d;
class Hero : public Role{
friend class Skill;
public:	
	static Hero* create(const std::string& name,FlightLayer* layer);
	static Hero* create(const std::string& name,FlightLayer* layer,int offsetX,int offsetY);
	void initHero();
	void initWithMessage(const HeroMessage& msg);
	
	virtual Point getHpSliderPos();
	
	inline void setSkill(SkillMessage s){m_skill = s;}
	inline SkillMessage getSkill(){return m_skill;}
	
	virtual void skill();
	
	void runStateEffect(int id);
	//�Ƿ��ڴ���״̬
	inline bool isSkilling(){return skilling;}
	//�Ƿ���ʹ�ô���
	inline bool isCanSkill(){return canUseSkill;}
	//�ָ�״̬
	void recover();

private:
	virtual void update(float dt);
	void update_state(float dt);
	void update_skill_cd(float dt);
private:
	SkillMessage m_skill;
	bool skilling;
	bool canUseSkill;
	
	float m_state_lastTime;


	float skillCD;

	Sprite* m_state_sprite;

};
#endif