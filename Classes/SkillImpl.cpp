#include "SkillImpl.h"
#include "Hero.h"
#include <list>
void SkillImpl::runSkill(int id,Hero* hero){
	switch(id){
	case 4001://skill_kb
	{
		hero->setHp(hero->getHp()/2);
		hero->setSpeed(hero->getSpeed()*2);
		hero->setAtkSpeed(hero->getAtkSpeed()*2);
		hero->setAtkHateValue(hero->getAtkHateValue()*3);
		break;
	}

	case 4002://skill_zl
	{
		Role_Ptr initTarget = hero->getAttackTarget();
		std::list<Role_Ptr> list = hero->getLayer()->getRolesArray();
		for(auto it = list.begin();it!=list.end();it++){
			if((**it)->getRoleType() == Role::ROLE_TYPE_HERO){
				hero->setAttackTarget(*it);
				hero->sendBullet();
			}
		}
		hero->setAttackTarget(initTarget);
		break;
	}

	case 4003://skill_ld
	{
		hero->setAtk(hero->getAtk()*2);
		hero->setBulletSpeed(hero->getBulletSpeed()*2);
		break;
	}
	default:
		break;
	}
}