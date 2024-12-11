#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/GameManager.h"
class Object
{
public:
	Object(sf::FloatRect r);
	Object(b2Vec2 pos, b2Vec2 size);
	Object();

	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(sf::RenderWindow& window);

	sf::FloatRect GetRect();
	sf::Vector2f GetPos();
	sf::Vector2f GetSize();

protected:
	void Delete();
	sf::FloatRect rect;
	GameManager* manager;
};