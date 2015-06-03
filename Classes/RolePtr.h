#ifndef _ROLEPTR_H_
#define _ROLEPTR_H_
#include "Role.h"
#include "FlightLayer.h"
class Role;
class FlightLayer;
/*Ŀ�������ö������Role��Դ(RAII),������ʱ�ǲ��ö���ָ��*/
class RolePtr{
public:
	static RolePtr* create(const std::string& name,FlightLayer* layer);
	Role* m_role;
	Role* getRole();
	~RolePtr();
private:
	RolePtr();
};
#endif