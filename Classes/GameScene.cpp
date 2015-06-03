#include "GameScene.h"
bool GameScene::init(){
	layer = FlightLayer::create();
	this->addChild(layer);
	return true;
}

void GameScene::setHeroTeam(const HeroMessage& h1,const HeroMessage& h2,const HeroMessage& h3){
	layer->initTeam(h1,h2,h3);
}

void GameScene::setMonsterDeq(deque<MonsterMessage> deq){
	layer->initMonsterDeq(deq);
}
