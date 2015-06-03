#include "SkillMessageUtil.h"
#include "json/document.h"
#include "json/rapidjson.h"
#define RETURN_IF(cond)           if((cond)) return

SkillMessageUtil* SkillMessageUtil::m_instance = nullptr;

SkillMessageUtil::SkillMessageUtil(){
	init();
}

SkillMessageUtil::~SkillMessageUtil(){
	CC_SAFE_DELETE(m_instance);
}


SkillMessageUtil* SkillMessageUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new SkillMessageUtil();
	}
	return m_instance;
}


void SkillMessageUtil::init(){
	string jsonStr = FileUtils::getInstance()->getStringFromFile("Json/SkillMessage.json");
	rapidjson::Document _mDoc;
	string mstr = jsonStr;
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["json"];
	
	CCLOG("Size = %d",pArr.Capacity());

	for(int i=0;i<pArr.Capacity();++i){
		SkillMessage skill;
		const rapidjson::Value &temp = pArr[i];
		int key = temp["id"].GetInt();
		skill.id = temp["id"].GetInt();
		skill.name = temp["name"].GetString();
		skill.desc = temp["desc"].GetString();
		skill.icon = temp["icon"].GetString();
		skill.begin_e = temp["begin_e"].GetInt();
		skill.state_e = temp["state_e"].GetInt();
		skill.hit_e = temp["hit_e"].GetInt();
		skill.lua = temp["lua"].GetString();
		skill.lastTime = temp["lastTime"].GetInt();
		skill.cd = temp["cd"].GetInt();
		skill.skill_bullet_img = temp["skill_bullet_img"].GetString();

		skillMap.insert(make_pair(key,skill));
	}
	CCLOG("SKILL MAP SIZE = %d",skillMap.size());
	return;
}

SkillMessage SkillMessageUtil::getMessageById(int id){
	auto it = skillMap.find(id);
	CCASSERT(it!=skillMap.end(),"can't get skill message of the id");
	return it->second;
}


