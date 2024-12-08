#include "EngineCore.h"
#include <iostream>
EngineCore::EngineCore()
	: engine(),
	renderer(window)
{
	int winWidth = 1050;
	int winHeight = 750;
	std::string name = "crazy game";
	window.create(sf::VideoMode(winWidth, winHeight), name);
	renderer.Start();
	Start();
}

void EngineCore::Start()
{
	std::cout << "Starting Engine" << std::endl;
	LoopEngine();
}

void EngineCore::LoopEngine()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine" << std::endl;
				window.close();
			}
		}

		sf::Time elapsed = gameClock.restart();
		accumulator += elapsed.asSeconds();

		while (accumulator >= timeStep) {
			engine.FixedUpdate();
			accumulator -= timeStep;
		}
		engine.Update();
		renderer.Render();
	}
}