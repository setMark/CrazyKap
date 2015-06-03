#include "ChooseLayer.h"
#include "GameScene.h"
#include "HeroMessageUtil.h"
#include "StageMessageUtil.h"
#include "MenuScene.h"

bool ChooseLayer::init(){
	pNode = GUIReader::getInstance()->widgetFromJsonFile("UI/ChooseLayerUI.json");
	this->addChild(pNode,0);

	Button* enterBtn = (Button*)Helper::seekWidgetByName(pNode,"enterBtn");
	enterBtn->addTouchEventListener(this,toucheventselector(ChooseLayer::startGame));

	Button* backBtn = (Button*)Helper::seekWidgetByName(pNode,"backBtn");
	backBtn->addTouchEventListener(this,toucheventselector(ChooseLayer::backToMenu));

	Button* leftBtn1 = (Button*)Helper::seekWidgetByName(pNode,"leftBtn1");
	leftBtn1->addTouchEventListener(this,toucheventselector(ChooseLayer::leftHero1));

	Button* leftBtn2 = (Button*)Helper::seekWidgetByName(pNode,"leftBtn2");
	leftBtn2->addTouchEventListener(this,toucheventselector(ChooseLayer::leftHero2));
	
	Button* leftBtn3 = (Button*)Helper::seekWidgetByName(pNode,"leftBtn3");
	leftBtn3->addTouchEventListener(this,toucheventselector(ChooseLayer::leftHero3));


	Button* rightBtn1 = (Button*)Helper::seekWidgetByName(pNode,"rightBtn1");
	rightBtn1->addTouchEventListener(this,toucheventselector(ChooseLayer::rightHero1));

	Button* rightBtn2 = (Button*)Helper::seekWidgetByName(pNode,"rightBtn2");
	rightBtn2->addTouchEventListener(this,toucheventselector(ChooseLayer::rightHero2));

	Button* rightBtn3 = (Button*)Helper::seekWidgetByName(pNode,"rightBtn3");
	rightBtn3->addTouchEventListener(this,toucheventselector(ChooseLayer::rightHero3));

	
	initHeroMsg();

	return true;
}


void ChooseLayer::loadHeroes(){
	map<int,HeroMessage> temp = HeroMessageUtil::getInstance()->getHeroMessageMap();
	for(auto it = temp.begin();it!=temp.end();it++){
		HeroMessage msg = (*it).second;
		HeroItem item(msg.name,msg.id,msg.r_name,msg.offset_x,msg.offset_y);
		heroArray.push_back(item);
	}
}

void ChooseLayer::initHeroMsg(){
	loadHeroes();
	
	hero_name1 = (Text*)Helper::seekWidgetByName(pNode,"heroName1");
	hero_name2 = (Text*)Helper::seekWidgetByName(pNode,"heroName2");
	hero_name3 = (Text*)Helper::seekWidgetByName(pNode,"heroName3");

	cur_hero1_index = 0;
	cur_hero2_index = 0;
	cur_hero3_index = 0;

	hero1 = nullptr;
	hero2 = nullptr;
	hero3 = nullptr;

	setCurHeroMsg(0,1);
	setCurHeroMsg(0,2);
	setCurHeroMsg(0,3);
}

void ChooseLayer::setCurHeroMsg(int index,int heroIndex){
	if(index < 0){
		index = index + heroArray.size();
	}

	if(index >= heroArray.size()){
		index = index - heroArray.size();
	}
	switch(heroIndex){
	case 1:
		cur_hero1_index = index;
		hero_name1->setText(heroArray[cur_hero1_index].name);
		if(hero1)	hero1->removeFromParentAndCleanup(true);
		hero1 = Armature::create(heroArray[cur_hero1_index].resourceName);
		hero1->setPosition(hero_name1->getPositionX()+heroArray[cur_hero1_index].o_x,
						   hero_name1->getPositionY()+heroArray[cur_hero1_index].o_y);
		hero1->getAnimation()->play("stand");
		this->addChild(hero1);
		break;
	case 2:
		cur_hero2_index = index;
		hero_name2->setText(heroArray[cur_hero2_index].name);
		if(hero2)	hero2->removeFromParentAndCleanup(true);
		hero2 = Armature::create(heroArray[cur_hero2_index].resourceName);
		hero2->setPosition(hero_name2->getPositionX()+heroArray[cur_hero2_index].o_x,
						   hero_name2->getPositionY()+heroArray[cur_hero2_index].o_y);
		hero2->getAnimation()->play("stand");
		this->addChild(hero2);
		break;
	case 3:
		cur_hero3_index = index;
		hero_name3->setText(heroArray[cur_hero3_index].name);
		if(hero3)	hero3->removeFromParentAndCleanup(true);
		hero3 = Armature::create(heroArray[cur_hero3_index].resourceName);
		hero3->setPosition(hero_name3->getPositionX()+heroArray[cur_hero3_index].o_x,
						   hero_name3->getPositionY()+heroArray[cur_hero3_index].o_y);
		hero3->getAnimation()->play("stand");
		this->addChild(hero3);
		break;
	default:
		break;
	
	}
}

//HeroItem

HeroItem::HeroItem(const std::string& name,const int id,const std::string& resourceName,const int ox,const int oy){
	this->name = name;
	this->resourceName = resourceName;
	this->id = id;
	this->o_x = ox;
	this->o_y = oy;
}
HeroItem::~HeroItem(){

}



//按钮对应回调函数

void ChooseLayer::startGame(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_ENDED){

		GameScene* scene = GameScene::create();
		scene->setHeroTeam(
						HeroMessageUtil::getInstance()->getMessageById(heroArray[cur_hero1_index].id),
						HeroMessageUtil::getInstance()->getMessageById(heroArray[cur_hero2_index].id),
						HeroMessageUtil::getInstance()->getMessageById(heroArray[cur_hero3_index].id)
		);
		scene->setMonsterDeq(StageMessageUtil::getInstance()->getMessageById(3001).monsterDeq);
		Director::getInstance()->replaceScene(scene);
	}
}

void ChooseLayer::leftHero1(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		setCurHeroMsg(cur_hero1_index - 1,1);
	}
}

void ChooseLayer::leftHero2(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		setCurHeroMsg(cur_hero2_index - 1,2);
	}
}

void ChooseLayer::leftHero3(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		setCurHeroMsg(cur_hero3_index - 1,3);
	}
}

void ChooseLayer::rightHero1(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		setCurHeroMsg(cur_hero1_index + 1,1);
	}
}

void ChooseLayer::rightHero2(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		setCurHeroMsg(cur_hero2_index + 1,2);
	}
}

void ChooseLayer::rightHero3(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		setCurHeroMsg(cur_hero3_index + 1,3);
	}
}



void ChooseLayer::backToMenu(Ref* pSender,TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_ENDED){
		Director::getInstance()->replaceScene(MenuScene::create());
	}
}