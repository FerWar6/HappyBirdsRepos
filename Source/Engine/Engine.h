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

	// When adding an object it gets added to markedForAddition 
	// and when deleting an object it gets added to markedForDeletion
	void AddObject(Object* obj);
	void DeleteObject(Object* obj);

	std::vector<Object*> objects;
	std::vector<Object*> markedForAddition;
	std::vector<Object*> markedForDeletion;

	PreLoader& GetPreLoader();
	InputManager& GetInputManager();
	GameManager& GetGameManager();
	CollisionManager& GetCollisionManager();

	void LoadScene(std::string name);
	void ReloadCurrentScene();
	void LoadObjectsIntoScene(std::string name);

	Scene* GetScene(std::string name);
	void OpenSceneSelection(); // Opens menu to choose a scene to edit
	void OpenSceneEditor(Scene scene);
	bool inEditMode = false;
	const int worldScale = 50; // TODO - is this the right place for worldScale?

private:
	PreLoader preLoader;
	CollisionManager collisionManager;
	GameManager gameManager;
	InputManager inputManager;
	sf::RenderWindow* window;

	Scene* currentScene;
	std::vector<Scene> allScenes;
	std::string scenePath = "Assets/Scenes/";
	void LoadScenes(); // Loads all of the scenes inside of scenePath into allScenes
	void ClearCurrentScene(); // Marks all object inside scene for deletion
};
