#ifndef _HMUTIL_H_
#define _HMUTIL_H_
#include "HeroMessage.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
#include <map>
using namespace cocos2d;

class HeroMessageUtil{
public:
	static HeroMessageUtil* getInstance();
	HeroMessage getMessageById(int id);
	map<int,HeroMessage> getHeroMessageMap();
	HeroMessageUtil();
	~HeroMessageUtil();
private:
	void initHeroMsgMap();
private:
	static HeroMessageUtil* m_instance;
	map<int,HeroMessage> heroMsgMap;
};
#endif