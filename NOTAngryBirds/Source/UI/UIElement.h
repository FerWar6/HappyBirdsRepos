#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
class UIElement
{
public:
	UIElement();

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void Render(sf::RenderWindow& window) {};
private:

};