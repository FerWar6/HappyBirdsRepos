#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/Engine.h"
#include "Engine/Renderer.h"
class EngineCore
{
public:
	EngineCore();
	void Start();
	void LoopEngine();
private:
	Engine engine;
	Renderer renderer;
	sf::RenderWindow window;

	sf::Clock gameClock;
	float accumulator = 0.0f;
	const float timeStep = 1.0f / 60; // 60 updates per second
};


