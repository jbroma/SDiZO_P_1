#include "stdafx.h"
#include "Container_P_Factory.h"
#include "Array_P.h"
#include "List_P.h"
#include "Binary_Heap_P.h"
#include "RB_Tree_P.h"

Container_P_Factory::Container_P_Factory()
{
	Register("Array", &Array_P::create);
	Register("List", &List_P::create);
	Register("Heap", &Binary_Heap_P::create);
	Register("RBTree", &RB_Tree_P::create);
}


Container_P_Factory::~Container_P_Factory()
{
	FactoryMap.clear();
}

void Container_P_Factory::Register(const std::string & container_name, CreateContainerFunc container_constructor)
{
	FactoryMap[container_name] = container_constructor;
}

Container_P * Container_P_Factory::CreateContainer(const std::string & container_name)
{
	FactoryMap_t::iterator it = FactoryMap.find(container_name);
	if (it != FactoryMap.end())
		return it->second();
	return nullptr;
}
