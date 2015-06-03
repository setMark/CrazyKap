#ifndef _MONSTER_MESSAGE_UTIL_
#define _MONSTER_MESSAGE_UTIL_
#include "MonsterMessage.h"
#include <map>
class MonsterMessageUtil{
public:
	static MonsterMessageUtil* getInstance();
	MonsterMessage getMessageById(int id);
	map<int,MonsterMessage> getMonsterMessageMap();
	MonsterMessageUtil();
	~MonsterMessageUtil();
private:
	void initMonsterMsgMap();
private:
	static MonsterMessageUtil* m_instance;
	map<int,MonsterMessage> monsterMsgMap;
};

#endif