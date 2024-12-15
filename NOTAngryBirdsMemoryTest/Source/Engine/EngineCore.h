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

	b2WorldId worldId;
};


