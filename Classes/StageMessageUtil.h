#ifndef _STAGE_MESSAGE_UTIL_
#define _STAGE_MESSAGE_UTIL_
#include <map>
#include "StageMessage.h"
class StageMessageUtil{
public:
	static StageMessageUtil* getInstance();
	StageMessage getMessageById(int id);
private:
	StageMessageUtil();
	~StageMessageUtil();
	void init();

private:
	static StageMessageUtil* m_instance;
	std::map<int,StageMessage> stageMap;
};
#endif