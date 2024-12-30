#include "Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include <iostream>

Object::Object()
	: manager(sl::GetGameManager())
{
	manager->enginePtr->AddObject(this);
}

Object::~Object()
{
}

Component* Object::GetComponent(std::string name)
{
	for (auto& comp : components) {
		if (comp->name == name) return comp;
	}
	std::cout << "returned nullptr from GetComponent\n";
	return nullptr;
}

void Object::AddComponent(Component* c)
{
	components.push_back(c);
}

bool Object::HasComponent(std::string componentName)
{
	for (auto& comp : components) {
		if (comp->name == componentName) return true;
	}
	return false;
}
