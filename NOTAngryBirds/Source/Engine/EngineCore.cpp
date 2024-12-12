#include "EngineCore.h"
#include <iostream>
EngineCore::EngineCore()
	: engine(),
	renderer(window)
{
	int winWidth = 1050;
	int winHeight = 1050;
	std::string name = "crazy game";
	window.create(sf::VideoMode(winWidth, winHeight), name);
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, -9.8f };
    worldId = b2CreateWorld(&worldDef);
	engine.GetManager()->SetWorldId(&worldId);
	engine.Start();
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
            b2World_Step(worldId, 0.005, 8);
            accumulator -= timeStep;
		}
		engine.Update();
		renderer.Render();
	}
}