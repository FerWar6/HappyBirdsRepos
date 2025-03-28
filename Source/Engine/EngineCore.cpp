#include "EngineCore.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Scenes/SceneEditor.h"
#include <iostream>

EngineCore::EngineCore()
	: engine(),
	inputManRef(engine.GetInputManager()),
	renderer(engine.objects)
{
	sl::SetEngineCore(this);
    b2WorldDef worldDef = b2DefaultWorldDef(); // Creates box2d world
    worldDef.gravity = { 0.0f, 9.8f };
    worldId = b2CreateWorld(&worldDef);
	sl::SetWorldId(&worldId);
	engine.Start();
	renderer.Start();
	Start();
}

float EngineCore::GetDeltaTime()
{
	return deltaTime;
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
			inputManRef.HandleEvent(event); // Used for mouse scroll

			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine \n";
				win.close();
			}
		}

		sf::Time elapsed = gameClock.restart();
		deltaTime = elapsed.asSeconds();
		accumulator += elapsed.asSeconds();

		engine.UpdateObjectsVector();

		while (accumulator >= timeStep) { // This is a while loop to catch up to repeat as many times as the accumulator missed
			engine.FixedUpdate();
            b2World_Step(worldId, timeStep, 4);

            accumulator -= timeStep;
		}
		engine.Update(); // Update game logic
		renderer.Render(); // Render game
	}
}