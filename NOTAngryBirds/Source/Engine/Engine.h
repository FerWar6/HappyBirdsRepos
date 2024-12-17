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
	std::vector<std::unique_ptr<Object>>& GetGameObjects();

private:
	b2DebugDraw debugDrawer;

	std::vector<std::unique_ptr<Object>> gameObjects;

	PreLoader preLoader;
	GameManager gameManager;
	LevelManager levelManager;
	InputManager inputManager;
};
