#pragma once
#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>
#include <box2d/box2d.h>
#include "Objects/Object.h"
#include "SFML/Graphics.hpp"
#include "Managers/GameManager.h"
#include <iostream>
class Renderer
{
public:
	Renderer(sf::RenderWindow& win);
	void Start();
	void Render();
private:
	b2WorldId worldId;

	b2BodyId groundId;
	sf::Vector2f groundSize = sf::Vector2f(1000, 10);
	b2BodyId circleBodyId1;
	b2BodyId bodyId1;
	float boxSize1 = 50;

	b2BodyId bodyId2;
	float boxSize2 = 15;

	sf::RenderWindow& window;
	GameManager* manager;
	std::vector<Object*> objectsToRender;
};