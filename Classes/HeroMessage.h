#ifndef _HEROMESSAGE_H_
#define _HEROMESSAGE_H_
#include <string>
using namespace std;
class HeroMessage{
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
	double atk_speed;
	bool naima;
	string bullet;
	int skill;
};
#endif