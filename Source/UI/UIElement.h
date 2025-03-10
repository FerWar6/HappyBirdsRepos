#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "DataTypes/Transform.h"
#include "DataTypes/Camera.h"
class UIElement
{
public:
	UIElement();

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void Render(sf::RenderWindow& window) {};
private:
	Camera& cam;
	Transform transform;
};