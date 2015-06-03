#ifndef _MONSTER_MESSAGE_H_
#define _MONSTER_MESSAGE_H_
#include <string>
using namespace std;
class MonsterMessage{
	public:
	int id;
	string name;
	string r_name;
	string r_png;
	string r_plist;
	string r_ExportJson;
	int offset_x;
	int offset_y;
	int atk_dis;
	int hp;
	int atk;
	int def;
	int speed;
	int atk_speed;
	bool naima;
	string bullet;
};

#endif