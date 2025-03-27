#pragma once
#include "DataTypes/Camera.h"
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
	Camera& GetCamera();
private:
	sf::RenderWindow window;
	Camera camera;
	std::vector<Object*>& objects;
};