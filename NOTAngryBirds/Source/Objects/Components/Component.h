#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
//#include "SFML/Graphics/RenderWindow.hpp"

class Object;

struct Component
{
	Component(Object& object, std::string n);
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void Render(sf::RenderWindow& window) {}
	Object& object;
	std::string name;
};
