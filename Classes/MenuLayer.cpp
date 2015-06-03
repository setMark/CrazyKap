#include "MenuLayer.h"
#include "ChooseScene.h"
bool MenuLayer::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* bg = Sprite::create("UI/menu_bg.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg,-1);

	MenuItemImage* beginBtn = MenuItemImage::create("UI/menu_beginBtn_h.png","UI/menu_beginBtn_n.png",CC_CALLBACK_1(MenuLayer::startGame,this));
	Menu* menu = Menu::create(beginBtn,NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);

	return true;
}

void MenuLayer::startGame(Ref* pSender){
	Director::getInstance()->replaceScene(ChooseScene::create());
}