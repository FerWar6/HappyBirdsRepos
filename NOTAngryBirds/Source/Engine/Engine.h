#pragma once

#include "Managers/GameManager.h"
#include "Engine/PreLoader.h"
#include "Objects/BuildingBlock.h"
class Engine
{
public:
	Engine();
	void Start();
	void Update();
	void FixedUpdate();
private:


	PreLoader preLoader;
	GameManager manager;
	BuildingBlock block;
};
