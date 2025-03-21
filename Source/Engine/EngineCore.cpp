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





			// Get contact events
			b2ContactEvents contactEvents = b2World_GetContactEvents(worldId);

			//std::cout << "==== Physics Debug Info ====\n";

			// Print contact hit events if any
			if (contactEvents.hitCount > 0)
			{
				std::cout << "Hit Events: " << contactEvents.hitCount << " events\n";
				for (int i = 0; i < contactEvents.hitCount; ++i)
				{
					const b2ContactHitEvent& hitEvent = contactEvents.hitEvents[i];
					std::cout << " Point: (" << hitEvent.point.x << ", " << hitEvent.point.y << ")"
						<< " Normal: (" << hitEvent.normal.x << ", " << hitEvent.normal.y << ")"
						<< " Speed: " << hitEvent.approachSpeed << " m/s\n";
				}
			}
			
			// Print body count (Example: Modify based on your API)
			int bodyCount = b2World_GetAwakeBodyCount(worldId);
			std::cout << "Total Bodies: " << bodyCount << "\n";

			// Print sensor events (if any)
			b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId);
			if (sensorEvents.beginCount > 0 || sensorEvents.endCount > 0)
			{
				std::cout << "Sensor Events: " << sensorEvents.beginCount << " begins, "
					<< sensorEvents.endCount << " ends\n";
			}

			// Print step completion
			//std::cout << "============================\n";






            accumulator -= timeStep;
		}
		engine.Update();
		renderer.Render();
	}
}