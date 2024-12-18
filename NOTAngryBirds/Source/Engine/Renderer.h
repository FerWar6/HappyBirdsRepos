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
	Renderer(sf::RenderWindow& win, std::vector<std::unique_ptr<Object>>& objRef);
	void Start();
	void Render();

	sf::Sprite grid;
private:

	int scale = 50;
	std::vector<std::unique_ptr<Object>>& gameObjectsRef;
	sf::RenderWindow& window;
	GameManager* manager;
	std::vector<Object*> objectsToRender;
};