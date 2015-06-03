#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"
#include "Role.h"
#include "RolePtr.h"
using namespace cocos2d;
class Role;
class Bullet : public Node{
public:
	static Bullet* createWithTarget(Role* sender,Role** target);
	bool initWithTarget(Role* sender,Role** target);
	void setDamage(int damage);
	void setHateValue(int value);
	~Bullet();
private:
	Sprite* m_bullet;
	Role* m_target;
	Role** m_targetPtr;
	virtual void update(float dt);
	int m_damage;
	int m_speed;
	Role* m_sender;
	int m_HateValue;
	int m_effect;
};
#endif