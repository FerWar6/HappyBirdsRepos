#pragma once
#include <iostream>
#include "SFML/Graphics/RenderWindow.hpp"
#include "DataTypes/Enums/ComponentTypes.h"
class Object;

class Component
{
public:
	Component(ComponentType t);
	virtual ~Component() = default;
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void Render(sf::RenderWindow& window) {}
	virtual void OnComponentAdded(Component& com) {}
	virtual Component* GetComponentPtr();
	virtual std::string GetSaveData();
	Object& object;
	ComponentType type;
	bool active;
};