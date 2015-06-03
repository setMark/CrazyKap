#ifndef _ROLE_H_
#define _ROLE_H_
#include "cocos2d.h"
#include "CocoStudio.h"
#include "RoleProtocol.h"
#include "FlightLayer.h"
#include "cocos-ext.h"
#include <string>
USING_NS_CC_EXT;
using namespace cocos2d;
using namespace cocostudio;
class FlightLayer;
class Role : public Node,public RoleProtocol{
friend class FlightLayer;
public:
	enum ROLE_STAT{
		ROLE_STAND,
		ROLE_MOVE,
		ROLE_ATTACK,
		ROLE_SKILL,
		ROLE_INJURED,
		ROLE_DIE,
		ROLE_NULL
	};
	
	enum ROLE_TYPE{
		ROLE_TYPE_NULL,
		ROLE_TYPE_HERO,
		ROLE_TYPE_MONSTER
	};
public:
	Role();
/*create 之前,请先确认已经将文件添加到ArmatureManager*/
	static Role* create(const std::string& name,FlightLayer* layer);
	virtual bool init(const std::string& name,FlightLayer* layer);
	void setControlable(bool b);
	virtual Rect getBoundingBox();
	void setHeightLight(bool b);
	void setEndPoint(const Point& p);
	Point getEndPoint();
	virtual inline void setArmOffsetX(int x){m_arm_offsetX = x;}
	virtual inline void setArmOffsetY(int y){m_arm_offsetY = y;}

protected:
	void initHpSlider();
	virtual Point getHpSliderPos();

protected:
/*update相关的*/
	virtual void update(float delta);
	virtual void update_checkHL();
	virtual void update_trace();
	virtual void update_pos();
	virtual void update_attackTarget();
	virtual void update_hp();

/*从RoleProtocol中继承下来的方法*/
public:
	virtual void stand();
	virtual void move();
	virtual void attack();
	virtual void skill();
	virtual void injured(int effect,int damage=0);
	virtual void die();

	virtual bool onTouchBegan(Touch* touch,Event* event);
	virtual void onTouchMoved(Touch* touch,Event* event);
	virtual void onTouchEnded(Touch* touch,Event* event);

	void onBondAnimationFinish(Armature* arm,MovementEventType type,const std::string& name);

protected:
	/*与显示相关的*/
	bool m_controlable;
	Armature* m_arm;
	int m_arm_offsetX;
	int m_arm_offsetY;

	Sprite* m_trace;
	Point m_endPoint;
	bool m_armFaceTo;	//朝向，默认为true，向左
	bool m_isHL;	//是否高亮显示
	Color3B m_defalutColor;
	ControlSlider* m_hpSlider;
	Sprite* m_selectCircle;


public:
	/*外部调用接口*/
	virtual inline void setDesPoint(const Point& p){m_desPoint = p;}

	virtual void setAttackTarget(Role** targetPtr);
	inline Role** getAttackTarget(){return m_attackTargetPtr;}
	//ID
	virtual inline int getId(){return m_id;}
	
	//角色状态、属性
	inline ROLE_STAT getRoleStat(){return en_stat;}
	inline ROLE_TYPE getRoleType(){return m_type;}
	
	//发射子弹
	void sendBullet();

	//跑技能效果（常用于被击中效果）
	void runSkillEffect(int skill_id,int loop =1);

public:
	//属性get/set

	//移动速度
	inline int getSpeed(){return m_speed;}
	inline void setSpeed(int speed){m_speed = speed;}
	inline int getInitSpeed(){return m_initSpeed;}
	inline void setInitSpeed(int speed){m_initSpeed = speed;}

	//攻击速度
	inline double getAtkSpeed(){return m_atkSpeed;}
	inline void setAtkSpeed(double speed){m_atkSpeed = speed;}
	inline double getInitAtkSpeed(){return m_initAtkSpeed;}
	inline void setInitAtkSpeed(double speed){m_initAtkSpeed = speed;}

	//生命值
	inline int getHp(){return m_hp;}
	inline void setHp(int hp){m_hp = hp;}
	inline int getInitHp(){return m_initHp;}
	inline void setInitHp(int hp){m_initHp = hp;}

	//攻击距离
	inline int getAttackDistance(){return m_attackDistance;}
	inline void setAttackDistance(int distance){m_attackDistance = distance;}
	inline int getInitAttackDistance(){return m_initAttackDistance;}
	inline void setInitAttackDistance(int distance){m_initAttackDistance = distance;}

	//攻击力
	inline int getAtk(){return m_atk;}
	inline void setAtk(int atk){m_atk = atk;}
	inline int getInitAtk(){return m_initAtk;}
	inline void setInitAtk(int atk){m_initAtk = atk;}
	
	//攻击附加仇恨值
	inline int getAtkHateValue(){return m_atkHateValue;}
	inline void setAtkHateValue(int value){m_atkHateValue = value;}
	
	//防御力
	inline void setDefence(int defence){m_defence = defence;}
	inline int getDefence(){return m_defence;}
	inline void setInitDefence(int def){m_initDefence = def;}
	inline int getInitDefence(){return m_initDefence;}


	//是不是奶妈
	inline bool isNaima(){return m_isNaima;}
	inline void setNaima(bool b){m_isNaima = b;}
    
	//子弹图片
	std::string getBulletImg();
	void setBulletImg(std::string img);
	
	//子弹速度
	inline int getBulletSpeed(){return m_bulletSpeed;}
	inline void setBulletSpeed(int speed){m_bulletSpeed = speed;}
	inline int getInitBulletSpeed(){return m_initBulletSpeed;}
	inline void setInitBulletSpeed(int speed){m_initBulletSpeed = speed;}

	//获取父控件
	inline FlightLayer* getLayer(){return m_layer;}
	
protected:
	/*与战斗相关的数据*/
	int m_id;	//id
	
	Role* m_attackTarget;
	Role** m_attackTargetPtr;//攻击目标

	Point m_desPoint;//目标位置
	
	ROLE_STAT en_stat;	//当前状态
	
	FlightLayer* m_layer;	//父控件


	int m_speed;	//移动速度
	int m_initSpeed;
	
	int m_attackDistance;	//攻击距离
	int m_initAttackDistance;

	int m_hp;//生命值
	int m_initHp;

	int m_atk;//攻击力
	int m_initAtk;

	int m_defence;//防御力
	int m_initDefence;

	ROLE_TYPE m_type;//角色类型：Monster Or Hero
	
	int m_atkHateValue;//攻击附带仇恨

	bool m_isNaima;//是不是奶妈
	
	std::string m_bulletImg;//子弹

	int m_bulletSpeed;//子弹速度
	int m_initBulletSpeed;

	double m_atkSpeed;//攻击速度
	double m_initAtkSpeed;

};
#endif