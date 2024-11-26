#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/GameManager.h"
class Object
{
public:
	Object(sf::FloatRect r);
	Object();

	virtual void Update();
	virtual void FixedUpdate();

	virtual void Render(sf::RenderWindow& window);
	sf::FloatRect GetRect();
	sf::Vector2f GetPos();
	sf::Vector2f GetSize();
private:
	void Delete();
	sf::FloatRect rect;
	GameManager* manager;
};