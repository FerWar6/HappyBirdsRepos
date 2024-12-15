#include "EngineCore.h"
#include <iostream>
#include <stdio.h>
#include <stack>
EngineCore::EngineCore()
	: engine()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, -9.8f };
    worldId = b2CreateWorld(&worldDef);
	engine.GetManager()->SetWorldId(&worldId);
	engine.Start();
	Start();
}

void EngineCore::Start()
{
	LoopEngine();
}

void EngineCore::LoopEngine()
{
	std::cout << "gvhgj";
}
/*while (window.isOpen()) 
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
}*/