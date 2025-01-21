#pragma once

#include "Managers/GameManager.h"
#include "Level/LevelManager.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
#include "Level/Grid.h"
#include "Engine/Scenes/Scene.h"

class Object;
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

	void LoadScene(std::string name);
private:
	GameManager gameManager;
	PreLoader preLoader;
	LevelManager levelManager;
	InputManager inputManager;
	
	Scene* currentScene;
	std::vector<Scene> allScenes;
	std::string scenePath = "Assets/Scenes/";
	void LoadScenes();
	void ClearCurrentScene();
	Scene* GetScene(std::string name);
};
