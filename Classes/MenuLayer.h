#ifndef _MENU_LAYER_H_
#define _MENU_LAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
private:
	void startGame(Ref* pSender);
};
#endif