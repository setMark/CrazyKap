#ifndef _SKILL_MSG_UTIL_
#define _SKILL_MSG_UTIL_
#include "SkillMessage.h"
#include "cocos2d.h"
#include <map>
using namespace cocos2d;
class SkillMessageUtil{
public:
	static SkillMessageUtil* getInstance();
	SkillMessage getMessageById(int id);
private:
	void init();
	SkillMessageUtil();
	~SkillMessageUtil();
private:
	static SkillMessageUtil* m_instance;
	std::map<int,SkillMessage> skillMap;

};
#endif