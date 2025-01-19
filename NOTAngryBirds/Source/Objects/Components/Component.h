#pragma once
#include <iostream>
#include "SFML/Graphics/RenderWindow.hpp"
#include "Engine/Enums/ComponentTypes.h"
class Object;

struct Component
{
	Component(ComponentType t);
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void Render(sf::RenderWindow& window) {}
	virtual void OnComponentAdded(Component& com) {}
	virtual Component* GetComponentPtr();
	virtual std::string GetSaveData();
	Object* object;
	ComponentType type;
};