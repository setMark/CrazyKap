#include "RolePtr.h"
RolePtr::RolePtr(){ } 
RolePtr::~RolePtr(){ }

RolePtr* RolePtr::create(const std::string& name,FlightLayer* layer){
	RolePtr* ret = new RolePtr();
    ret->m_role = Role::create(name,layer);
	return ret;
}

Role* RolePtr::getRole(){
	return m_role;
}

