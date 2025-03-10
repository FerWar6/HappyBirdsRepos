#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Engine/Engine.h"
#include "Engine/Renderer.h"

class EngineCore
{
public:
	EngineCore();
private:
	void Start();
	void LoopEngine();
	Engine engine;
	Renderer renderer;
	sf::RenderWindow window;

	b2WorldId worldId;
	sf::Clock gameClock;

	int fixedUpdateFrames = 60;
	const float timeStep = 1.0f / fixedUpdateFrames;
	float deltTime = 0.0f;
	float accumulator = 0.0f;
};


