#include "MonsterMessageUtil.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
using namespace cocos2d;

#define RETURN_IF(cond)           if((cond)) return

MonsterMessageUtil* MonsterMessageUtil::m_instance = nullptr;

MonsterMessageUtil::MonsterMessageUtil(){
	initMonsterMsgMap();
}

void MonsterMessageUtil::initMonsterMsgMap(){
	std::string  jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile("Json/MonsterMessage.json");
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError()||!_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["json"];

	CCLOG("Size = %d",pArr.Capacity());

	for(int i=0;i<pArr.Capacity();++i){
		MonsterMessage h;
		const rapidjson::Value &temp = pArr[i];
		int id = temp["id"].GetInt();
		h.id = temp["id"].GetInt();
		h.name = temp["name"].GetString();
		h.r_name = temp["r_name"].GetString();
		h.r_png = temp["r_png"].GetString();
		h.r_plist = temp["r_plist"].GetString();
		h.r_ExportJson = temp["r_ExportJson"].GetString();
		h.offset_x = temp["offset_x"].GetInt();
		h.offset_y = temp["offset_y"].GetInt();
		h.atk_dis = temp["atk_dis"].GetInt();
		h.hp = temp["hp"].GetInt();
		h.atk = temp["atk"].GetInt();
		h.def = temp["def"].GetInt();
		h.speed = temp["speed"].GetInt();
		h.atk_speed = temp["atk_speed"].GetDouble();
		int b = temp["naima"].GetInt();
		h.naima = b==0?false:true;
		h.bullet = temp["bullet_img"].GetString();

		monsterMsgMap.insert(make_pair(id,h));

		CCLOG("h : %s",h.r_png.c_str());
	}
	CCLOG("MapSize = %d",monsterMsgMap.size());

}


MonsterMessageUtil::~MonsterMessageUtil(){
	CC_SAFE_DELETE(m_instance);
}

MonsterMessageUtil* MonsterMessageUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new MonsterMessageUtil();
	}
	return m_instance;
}

map<int,MonsterMessage> MonsterMessageUtil::getMonsterMessageMap(){
	return monsterMsgMap;
}

MonsterMessage MonsterMessageUtil::getMessageById(int id){
	auto it =  monsterMsgMap.find(id);
	CCASSERT(it!=monsterMsgMap.end(),"can't get monster msg of the id");
	return (*it).second;
}