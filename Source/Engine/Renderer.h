#pragma once
#include "Objects/Object.h"
#include <box2d/box2d.h>
#include <SFML/Graphics/RenderWindow.hpp>

class EngineCore;
class Renderer
{
public:
	Renderer(std::vector<Object*>& objRef);
	void Start();
	void Render();
	sf::RenderWindow& GetWindow();

private:
	sf::RenderWindow window;
	std::vector<Object*>& objects;
};