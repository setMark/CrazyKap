#include "ChooseScene.h"
#include "ChooseLayer.h"

bool ChooseScene::init(){
	ChooseLayer* layer = ChooseLayer::create();
	this->addChild(layer);
	return true;
}