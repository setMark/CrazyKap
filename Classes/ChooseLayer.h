#ifndef _CHOOSELAYER_H_
#define _CHOOSELAYER_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
class HeroItem;
class ChooseLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(ChooseLayer);
private:
	//加载可选英雄
	void loadHeroes();
	//初始化
	void initHeroMsg();
	//设置当前英雄
	void setCurHeroMsg(int index,int heroIndex);

	//按钮回调函数
	void startGame(Ref* pSender,ui::TouchEventType type);

	void leftHero1(Ref* pSender,ui::TouchEventType type);
	void rightHero1(Ref* pSender,ui::TouchEventType type);

	void leftHero2(Ref* pSender,ui::TouchEventType type);
	void rightHero2(Ref* pSender,ui::TouchEventType type);

	void leftHero3(Ref* pSender,ui::TouchEventType type);
	void rightHero3(Ref* pSender,ui::TouchEventType type);

	void backToMenu(Ref* pSender,ui::TouchEventType type);

private:
	std::vector<HeroItem> heroArray;
	Text* hero_name1;
	Text* hero_name2;
	Text* hero_name3;

	Widget* pNode;

	int cur_hero1_index;
	int cur_hero2_index;
	int cur_hero3_index;

	Armature* hero1;
	Armature* hero2;
	Armature* hero3;
};

class HeroItem : public Ref{
friend class ChooseLayer;
public:
	HeroItem(const std::string& name,const int id,const std::string& resourceName,const int o_x,const int o_y);
	~HeroItem();
private:
	std::string name;
	std::string resourceName;
	int id;
	int o_x;
	int o_y;
};
#endif