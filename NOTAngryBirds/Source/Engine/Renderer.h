#pragma once
#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>
#include <box2d/box2d.h>
#include "Objects/Object.h"
#include "SFML/Graphics.hpp"
#include "Managers/GameManager.h"
#include <iostream>

class EngineCore;
class Renderer
{
public:
	Renderer(sf::RenderWindow& win);
	void Start();
	void Render();
private:

	//int scale = 50;
	//b2WorldId worldId;

	//b2BodyId groundId;
	//b2BodyId cubeId1;
	//b2BodyId cubeId2;

	sf::RenderWindow& window;
	GameManager* manager;
	std::vector<Object*> objectsToRender;
};