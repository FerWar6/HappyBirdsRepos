#include "EngineCore.h"
#include "Managers/ServiceLocator.h"
#include "Level/LevelEditor.h"
#include <wtypes.h>
#include <iostream>
#include <stdio.h>

EngineCore::EngineCore()
	: engine(),
	renderer(engine.objects)
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 9.8f };
    worldId = b2CreateWorld(&worldDef);
	sl::SetWorldId(&worldId);
	sl::SetWindow(&window);
	
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
	//TODO - maybe open a window to check if the player want to open edit mode or play the game
	bool editorMode = true;
	if (editorMode) {
		engine.inEditMode = true;
		LevelEditor editor;
		engine.inEditMode = false;
	}

	int winWidth = 1500;
	int winHeight = 900;
	std::string windowName = "Happy Birds";
	window.create(sf::VideoMode(winWidth, winHeight), windowName);

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