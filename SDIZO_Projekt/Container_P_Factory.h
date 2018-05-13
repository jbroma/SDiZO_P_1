#pragma once
#include <map>
#include <string>

#include "Container_P.h"


typedef Container_P* (*CreateContainerFunc)(void);

class Container_P_Factory
{
private:
	Container_P_Factory();
	Container_P_Factory(const Container_P_Factory &);

	Container_P_Factory &operator=(const Container_P_Factory &)
	{
		return *this;
	}
	

	typedef std::map<std::string,CreateContainerFunc> FactoryMap_t;
	FactoryMap_t FactoryMap;

public:
	~Container_P_Factory();

	static Container_P_Factory * Get()
	{
		static Container_P_Factory instance;
		return &instance;
	}

	void Register(const std::string &container_name, CreateContainerFunc container_constructor);
	Container_P * CreateContainer(const std::string &container_name);
};

