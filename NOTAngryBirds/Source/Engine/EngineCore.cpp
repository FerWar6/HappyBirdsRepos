#include "EngineCore.h"
#include <iostream>
#include <stdio.h>
EngineCore::EngineCore()
	: engine(),
	renderer(window, engine.objects)
{
	int winWidth = 1500;
	int winHeight = 900;
	std::string name = "Happy Birds";
	window.create(sf::VideoMode(winWidth, winHeight), name);
	engine.GetManager()->SetWindow(&window);
	window.setPosition(sf::Vector2i(200,65));
	sf::Style::Close;

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 9.8f };
    worldId = b2CreateWorld(&worldDef);
	engine.GetManager()->SetWorldId(&worldId);
	
	engine.Start();
	renderer.Start();
	Start();
}

void EngineCore::Start()
{
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
		engine.UpdateObjectsVector();

		sf::Time elapsed = gameClock.restart();
		accumulator += elapsed.asSeconds();

		//TO-DO: check for any updates in gameobjects
		while (accumulator >= timeStep) {
			//std::cout << accumulator << "\n";
			engine.FixedUpdate();
            b2World_Step(worldId, timeStep, 4);
            accumulator -= timeStep;
		}
		engine.Update();
		renderer.Render();
	}
}