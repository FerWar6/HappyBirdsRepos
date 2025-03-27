#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "DataTypes/Transform.h"
#include "DataTypes/SceneEditorCamera.h"
class UIElement
{
public:
	UIElement();

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void Render(sf::RenderWindow& window) {};
private:
	SceneEditorCamera& cam;
	Transform transform;
};