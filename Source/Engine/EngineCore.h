#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Engine/Engine.h"
#include "Engine/Renderer.h"

class EngineCore
{
public:
	EngineCore();
	void SetPauseWorld(bool pause); // May be useless when resetting a level concidering the level already stopped moving when opening the stopmenu
private:
	void Start();
	void LoopEngine();
	Engine engine;
	InputManager& inputManRef;
	Renderer renderer;

	b2WorldId worldId;
	bool worldPaused;
	sf::Clock gameClock;
	sf::RenderWindow* window;
	int fixedUpdateFrames = 60;
	const float timeStep = 1.0f / fixedUpdateFrames;
	float deltTime = 0.0f;
	float accumulator = 0.0f;
};
