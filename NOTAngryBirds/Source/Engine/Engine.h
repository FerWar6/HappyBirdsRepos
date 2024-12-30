#pragma once

#include "Managers/GameManager.h"
#include "Managers/LevelManager.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
#include "Objects/PhysicsObject.h"
#include "Level/Grid.h"
#include "Level/Launcher.h"

class Engine
{
public:
	Engine();
	void Start();
	void Update();
	void FixedUpdate();
	void UpdateObjectsVector();

	GameManager* GetManager();


	void AddObject(Object* obj);
	void DeleteObject(Object* obj);

	std::vector<Object*> objects;

	std::vector<Object*> markedForAddition;
	std::vector<Object*> markedForDeletion;
	GameManager& GetGameManager();
	PreLoader& GetPreLoader();
	LevelManager& GetLevelManager();
	InputManager& GetInputManager();
private:
	GameManager gameManager;
	PreLoader preLoader;
	LevelManager levelManager;
	InputManager inputManager;
};
