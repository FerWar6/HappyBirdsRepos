#pragma once
#include "Engine/Engine.h"
#include "Engine/Renderer.h"
#include <SFML/Graphics/RenderWindow.hpp>

class EngineCore
{
public:
	EngineCore();
	const int worldScale = 50;
private:
	void Start();
	void LoopEngine();
	Engine engine;
	Renderer renderer;
	sf::RenderWindow* window;
	InputManager& inputManRef;
	b2WorldId worldId;

	// Fixed update functionality
	sf::Clock gameClock;
	int fixedUpdateFrames = 60;
	const float timeStep = 1.0f / fixedUpdateFrames;
	float deltTime = 0.0f;
	float accumulator = 0.0f;
};
