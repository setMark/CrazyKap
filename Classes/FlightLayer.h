#ifndef _FLIGHT_LAYER_H_
#define _FLIGHT_LAYER_H_
#include "cocos2d.h"
#include <list>
#include <algorithm>
#include <deque>
#include "Role.h"
#include "Bullet.h"
#include "HeroMessage.h"
#include "MonsterMessage.h"
#include "Skill.h"

using namespace std;
using namespace cocos2d;
class Role;
class Bullet;
typedef Role** Role_Ptr;
class FlightLayer : public Layer{
friend class Role;
/*�ⲿ�ṩ�ӿ�*/
public:
	virtual bool init();
	CREATE_FUNC(FlightLayer);
	void addRole(Role* r);
	std::list<Role_Ptr> getRolesArray(){return m_rolesArray;}

	void initTeam(const HeroMessage& h1,const HeroMessage& h2,const HeroMessage& h3);
	void initMonsterDeq(deque<MonsterMessage> deq);

/*�ڲ�ʹ�ú���*/
private:
	virtual void update(float delta);
	void initListener();
	bool comparePosY(Role_Ptr a,Role_Ptr b);
	/*����layer��role�ĵ��Ŵ���*/
	void refreshLocalZOrder();
	/*����layer�еĿ�ָ��*/
	void cleanNullPtrInArray();
	/*����m_cur_control����ȷ��*/
	void updateMyControl();
	/*���ƹ���ĳ���*/
	void updateMonster();

	void updateSkill();

	virtual bool onTouchBegan(Touch* touch,Event* event);
	virtual void onTouchMoved(Touch* touch,Event* event);
	virtual void onTouchEnded(Touch* touch,Event* event);
	/*����ӵ�*/
	void addBullet(Role* sender,Role_Ptr targetPtr);
/*���Ա����*/
private:
	std::list<Role_Ptr> m_rolesArray;
	Role* m_cur_control;
	Role_Ptr m_cur_controlPtr;
	deque<MonsterMessage> m_monsterDeq;
	Skill* m_skill;
};
#endif