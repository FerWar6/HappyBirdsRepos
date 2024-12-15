#pragma once

#include "Managers/GameManager.h"
#include "Managers/LevelManager.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
#include "Objects/PhysicsObject.h"
class Engine
{
public:
	Engine();
	void Start();
	void Update();
	void FixedUpdate();

	GameManager* GetManager();
private:
	GameManager gameManager;
	std::vector<Object> allObjects;
};
