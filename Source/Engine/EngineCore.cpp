#include "EngineCore.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Scenes/SceneEditor.h"
#include <wtypes.h>
#include <iostream>
#include <stdio.h>

EngineCore::EngineCore()
	: engine(),
	inputManRef(engine.GetInputManager()),
	renderer(engine.objects)
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 9.8f };
    worldId = b2CreateWorld(&worldDef);
	sl::SetWorldId(&worldId);
	b2World_SetHitEventThreshold(worldId, 5);
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
	sf::RenderWindow& win = *window;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event)) {
			inputManRef.HandleEvent(event);

			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine \n";
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