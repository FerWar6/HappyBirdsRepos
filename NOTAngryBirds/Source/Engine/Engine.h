#pragma once

#include "Managers/GameManager.h"
#include "Managers/LevelManager.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
#include "Objects/PhysicsObject.h"
#include "Level/Grid.h"
class Engine
{
public:
	Engine();
	void Start();
	void Update();
	void FixedUpdate();

	GameManager* GetManager();
	std::vector<std::unique_ptr<Object>>& GetGameObjects();
	GameManager gameManager;
	PreLoader preLoader;

private:
	b2DebugDraw debugDrawer;

	std::vector<std::unique_ptr<Object>> gameObjects;
	LevelManager levelManager;
	InputManager inputManager;
};
