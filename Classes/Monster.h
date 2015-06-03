#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "Role.h"
#include "FlightLayer.h"
#include <list>
#include "MonsterMessage.h"
class Monster : public Role{
public:
	Monster();
	static Monster* create(const std::string& name,FlightLayer* layer);
	void initMonster();
	
	virtual Point getHpSliderPos();
	void addHateValue(Role* sender,int HateValue);

    void initWithMessage(const MonsterMessage& msg);
private:
	virtual void update(float dt);
	void updateMonsterAttackTarget();
	void initHateMap();
	void refreshHateMap();
	virtual void injured(int damage);
	Role** getHatest();
	bool cmpHate(const pair<Role_Ptr,int> &x,const pair<Role_Ptr,int> &y);
private:
	std::map<Role_Ptr,int> hateMap;
	
	bool debugMode;
};
#endif