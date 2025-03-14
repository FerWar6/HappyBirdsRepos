#include "EngineCore.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Scenes/SceneEditor.h"
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
	
	engine.Start();
	renderer.Start();
	Start();
}

void EngineCore::Start()
{
	window = &sl::GetWindow();
	LoopEngine();
}

void EngineCore::LoopEngine()
{
	//TODO - maybe open a window to check if the player want to open edit mode or play the game
	//bool editorMode = true;
	//if (editorMode) {
	//	engine.inEditMode = true;
	//	SceneEditor editor;
	//	engine.inEditMode = false;
	//}
	sf::RenderWindow& win = *window;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine" << std::endl;
				win.close();
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