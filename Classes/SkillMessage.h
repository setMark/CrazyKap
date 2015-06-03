#ifndef _SKILL_MESSAGE_H_
#define _SKILL_MESSAGE_H_
#include <string>
using namespace std;
class SkillMessage{
public:
	int id;
	string name;
	string desc;
	string icon;
	int begin_e;
	int state_e;
	int hit_e;
	string lua;
	int lastTime;
	int cd;
	string skill_bullet_img;
};
#endif