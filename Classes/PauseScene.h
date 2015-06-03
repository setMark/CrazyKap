#ifndef _PAUSE_SCENE_H_
#define _PAUSE_SCENE_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ChooseScene.h"
using namespace cocostudio;
using namespace ui;
using namespace cocos2d;
class PauseScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(PauseScene);
private:
	void continueGame(Ref* pSender,TouchEventType type);
	void stopGame(Ref* pSender,TouchEventType type);
};
#endif