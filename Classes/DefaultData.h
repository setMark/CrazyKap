#ifndef _DEFAULTDATA_H_
#define _DEFAULTDATA_H_


const int HERO_GUNER_DEFAULT_ATTACK_DISTANCE = 200;


const int BULLET_DEFAULT_DAMAGE = 20;
const int HERO_ATK_HATE_VALUE = 10;


static int UNIQUE_ID = 1;
inline int getUniqueId(){return UNIQUE_ID++;}

const int ROLE_DEFAULT_SPEED = 2;

const int ROLE_DEFAULT_HP = 100;

const int ROLE_DEFAULT_DEF = 5;

const int ROLE_DEFAULT_ATK = 20;

const int ROLE_DEFAULT_ATK_DIS = 100;

const double ROLE_DEFAULT_ATK_SPEED = 1.0f;

const int ROLE_DEFAULT_BULLET_SPEED = 12;
#endif