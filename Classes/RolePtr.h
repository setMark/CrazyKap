#ifndef _ROLEPTR_H_
#define _ROLEPTR_H_
#include "Role.h"
#include "FlightLayer.h"
class Role;
class FlightLayer;
/*目的是想用对象管理Role资源(RAII),不过暂时是采用二级指针*/
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