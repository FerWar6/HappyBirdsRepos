#pragma once
#include <iostream>
#include "SFML/Graphics/RenderWindow.hpp"
#include "DataTypes/Enums/ComponentTypes.h"
class Object;

class Component
{
public:
	Component(ComponentType t);
	virtual ~Component() = default; // Deconstructor necesairy for calling deconstructor of varients of abstract class
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void Render(sf::RenderWindow& window) {}
	virtual std::string GetSaveData();
	Object& object; // Ref to the object the component is attached to
	ComponentType type; // The component type stored in enum
	bool active;
};