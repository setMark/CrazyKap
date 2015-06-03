#include "MenuScene.h"
#include "MenuLayer.h"
#include "HeroMessageUtil.h"
#include "MonsterMessageUtil.h"
#include "StageMessageUtil.h"
bool MenuScene::init(){
	preLoadingSomethings();
	MenuLayer* layer = MenuLayer::create();
	this->addChild(layer);
	return true;
}

void MenuScene::preLoadingSomethings(){
	
	std::map<int,HeroMessage> temp = HeroMessageUtil::getInstance()->getHeroMessageMap();
	

	for(auto it = temp.begin();it!=temp.end();it++){
		HeroMessage temp = it->second;
		std::string png = "BoneAnimate/" + temp.r_png;
		std::string plist = "BoneAnimate/" + temp.r_plist;
		std::string EJ = "BoneAnimate/" + temp.r_ExportJson;
		ArmatureDataManager::getInstance()->addArmatureFileInfo(png,plist,EJ);
	}

	std::map<int,MonsterMessage> monTemp = MonsterMessageUtil::getInstance()->getMonsterMessageMap();
	for(auto it = monTemp.begin();it!=monTemp.end();++it){
		MonsterMessage temp = it->second;
		std::string png = "BoneAnimate/" + temp.r_png;
		std::string plist = "BoneAnimate/" + temp.r_plist;
		std::string EJ = "BoneAnimate/" + temp.r_ExportJson;
		ArmatureDataManager::getInstance()->addArmatureFileInfo(png,plist,EJ);
	}

	StageMessageUtil::getInstance();
}