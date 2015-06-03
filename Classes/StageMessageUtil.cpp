#include "StageMessageUtil.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "MonsterMessageUtil.h"
#include <sstream>
using namespace cocos2d;

#define RETURN_IF(cond)           if((cond)) return

StageMessageUtil* StageMessageUtil::m_instance = nullptr;


StageMessageUtil::StageMessageUtil(){
	init();
}

StageMessageUtil::~StageMessageUtil(){
	CC_SAFE_DELETE(m_instance);
}

StageMessageUtil* StageMessageUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new StageMessageUtil();
	}
	return m_instance;
}

void StageMessageUtil::init(){

	std::string  jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile("Json/StageMessage.json");
	rapidjson::Document _mDoc;

	std::string mstr = jsonStr;
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError()||!_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["json"];

	CCLOG("Size = %d",pArr.Capacity());

	for(int i=0;i<pArr.Capacity();++i){
		StageMessage stage;
		const rapidjson::Value &temp = pArr[i];
		int key = temp["id"].GetInt();
		stage.id = temp["id"].GetInt();
		stage.name = temp["name"].GetString();
		stage.boss = temp["boss"].GetInt();
		stage.reward_money = temp["reward_money"].GetInt();
		stage.reward_exp = temp["reward_exp"].GetInt();
		stage.reward_item = temp["reward_item"].GetString();
		
		string monsterStr = temp["monster"].GetString();
		char c[64];
		strcpy(c,monsterStr.c_str());
		char* s = strtok(c,"|");
		while(s != NULL){
			int id_num;
			stringstream ss;
			ss << s;
			ss >> id_num;
			CCLOG("GET ID:%d",id_num);
			MonsterMessage msg = MonsterMessageUtil::getInstance()->getMessageById(id_num);
			stage.monsterDeq.push_back(msg);
			s = strtok(NULL,"|");
		}
		CCLOG("DEQ SIZE = %d",stage.monsterDeq.size());
		stageMap.insert(make_pair(key,stage));
	}
	CCLOG("STAGE MAP SIZE = %d",stageMap.size());
	return;
}

StageMessage StageMessageUtil::getMessageById(int id){
	auto it = stageMap.find(id);

	CCASSERT(it!=stageMap.end(),"can't get state msg of the id");
	return it->second;
}