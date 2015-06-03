#include "PauseScene.h"

bool PauseScene::init(){
	Widget* pNode = GUIReader::getInstance()->widgetFromJsonFile("UI/PauseUI.json");
	this->addChild(pNode,0);

	Button* continueBtn = (Button*)Helper::seekWidgetByName(pNode,"continueBtn");
	continueBtn->addTouchEventListener(this,toucheventselector(PauseScene::continueGame));
	Button* stopBtn = (Button*)Helper::seekWidgetByName(pNode,"stopBtn");
	stopBtn->addTouchEventListener(this,toucheventselector(PauseScene::stopGame));
	return true;
}

void PauseScene::continueGame(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		CCLOG("GAME CONTINUE");
		Director::getInstance()->popScene();
	}
}

void PauseScene::stopGame(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		CCLOG("GAME STOP");
		Director::getInstance()->replaceScene(ChooseScene::create());
	}
}