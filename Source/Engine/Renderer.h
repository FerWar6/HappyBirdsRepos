#pragma once
#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>
#include <box2d/box2d.h>
#include "Objects/Object.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class EngineCore;
class Renderer
{
public:
	//render request
	Renderer(std::vector<Object*>& objRef);
	void Start();
	void Render();

	sf::Sprite grid;
private:

	int scale = 50;
	std::vector<Object*>& gameObjectsRef;
	sf::RenderWindow* window;
	std::vector<Object*> objectsToRender;
};