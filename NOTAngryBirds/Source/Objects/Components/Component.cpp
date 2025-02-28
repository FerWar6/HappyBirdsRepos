#include "Component.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Object.h"
Component::Component(ComponentType t)
	: type(t),
	object(nullptr)
{
	sl::GetSelectedObj().AddComponent(this);
}

Component* Component::GetComponentPtr()
{
	return this;
}

std::string Component::GetSaveData()
{
	return std::string();
}
