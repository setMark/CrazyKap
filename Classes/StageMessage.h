#ifndef _STAGE_MESSAGE_H_
#define _STAGE_MESSAGE_H_
#include <string>
#include <deque>
#include "MonsterMessage.h"
using namespace std;
class StageMessage{
public:
	int id;
	string name;
	int reward_money;
	int reward_exp;
	int boss;
	string reward_item;
	deque<MonsterMessage> monsterDeq;
};
#endif