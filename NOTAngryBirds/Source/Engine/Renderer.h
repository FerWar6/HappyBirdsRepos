#pragma once
#include "Objects/Object.h"
#include "SFML/Graphics.hpp"
#include "Managers/GameManager.h"
class Renderer
{
public:
	Renderer(sf::RenderWindow& win);
	void Render();
private:
	sf::RenderWindow& window;
	GameManager* manager;
	std::vector<Object*> objectsToRender;
};

