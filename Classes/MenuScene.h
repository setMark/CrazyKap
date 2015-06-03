#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_
#include "cocos2d.h"
#include "CocoStudio.h"
#include "cocos-ext.h"

using namespace ui;
USING_NS_CC;
class MenuScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(MenuScene);
private:
	void preLoadingSomethings();
};
#endif