#include "Component.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Object.h"
Component::Component(std::string n)
	: name(n),
	object(nullptr)
{
	sl::GetSelectedObj()->AddComponent(this);
}