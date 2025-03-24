#pragma once
#include "Managers/InputManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/GameManager.h"
#include "Engine/PreLoader.h"
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

	void AddObject(Object* obj);
	void DeleteObject(Object* obj);

	std::vector<Object*> objects;
	std::vector<Object*> markedForAddition;
	std::vector<Object*> markedForDeletion;

	PreLoader& GetPreLoader();
	//LevelManager& GetLevelManager();
	InputManager& GetInputManager();
	GameManager& GetGameManager();

	void LoadScene(std::string name);
	void ReloadCurrentScene();

	void OpenSceneSelection();
	void OpenSceneEditor(Scene scene);
	bool inEditMode = false;
	const int worldScale = 50;
private:
	PreLoader preLoader;
	CollisionManager collisionManager;
	GameManager gameManager;
	//LevelManager levelManager;
	InputManager inputManager;
	sf::RenderWindow* window;

	Scene* currentScene;
	std::vector<Scene> allScenes;
	std::string scenePath = "Assets/Scenes/";
	void LoadScenes();
	void ClearCurrentScene();
	Scene* GetScene(std::string name);
};
