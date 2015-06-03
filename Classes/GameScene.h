#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "cocos2d.h"
#include "HeroMessage.h"
#include "MonsterMessage.h"
#include "FlightLayer.h"
using namespace cocos2d;
class GameScene : public Scene{
public:
	CREATE_FUNC(GameScene);
	void setHeroTeam(const HeroMessage& h1,const HeroMessage& h2,const HeroMessage& h3);
	void setMonsterDeq(deque<MonsterMessage> deq);
private:
	virtual bool init();
	FlightLayer* layer;
};

#endif