#ifndef _SKILL_H_
#define _SKILL_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class Hero;
class Skill : public Node{
public:
    bool init(Hero* h);
	static Skill* create(Hero* h);
	void onTouchDown(Ref* pSender,ui::TouchEventType type);
	Hero* getHero();
	void updateCD(float delta);
private:
	ui::Button* skillIcon;
	Hero* m_hero;
	Label* cdTime;
};
#endif