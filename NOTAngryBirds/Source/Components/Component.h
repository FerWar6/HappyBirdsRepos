#pragma once
#include <iostream>
struct Component
{
	Component(std::string n)
	{
		name = n;
	};
	virtual void ComponentBehaviour() {};
	std::string name;
};
