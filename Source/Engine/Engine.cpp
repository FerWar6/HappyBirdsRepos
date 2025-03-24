#include "Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Managers/ServiceLocator.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

Engine::Engine()
	: preLoader(),
	inputManager(),
	collisionManager(),
	gameManager(*this),
	currentScene(nullptr),
	window(nullptr)
{
	sl::SetEngine(this);
	preLoader.buttonFunctions.LinkButtonFunctions(this, &gameManager);
	LoadScenes();
}

void Engine::Start()
{
	collisionManager.Start();
	window = &sl::GetWindow();

	LoadScene("MainMenu");

	//Object* obj = new Object(sf::Vector2f(150, 700), 0, sf::Vector2f(1, 1));
	//obj->AddComponent<SpriteRenderer>("StartButton", true);
	//obj->AddComponent<Button>(LOADSCENE_LEVELSELECT);

	//Object* obj = new Object(sf::Vector2f(700, 700), 0, sf::Vector2f(50, 50));
	//obj->AddComponent<SpriteRenderer>("CannonBall", false, false, sf::Vector2f(0, 0));
	//obj->AddComponent<CircleRigidbody>(b2_dynamicBody, 1, sl::GetWorldId());
	//obj->AddComponent<DestructibleItem>(100);
	//obj->AddComponent<WinConditionItem>(1000);
	//std::cout << obj->GetSaveData() << "\n";
}

void Engine::Update()
{
	inputManager.SetMousePos(*window);
	inputManager.UpdateInputs();
	gameManager.Update();
	for (auto obj : objects) {
		obj->Update();
	}
	inputManager.buttonMan.UpdateButtonCalls();
}

void Engine::FixedUpdate()
{
	collisionManager.UpdateCollisions();
	for (auto& obj : objects) {
		obj->FixedUpdate();
	}
}

void Engine::UpdateObjectsVector()
{
	if (!markedForAddition.empty()) {
		objects.insert(objects.end(), markedForAddition.begin(), markedForAddition.end());
		markedForAddition.clear();
	}
	if (!markedForDeletion.empty()) {
		for (Object* obj : markedForDeletion) {
			auto it = std::find(objects.begin(), objects.end(), obj);
			if (it != objects.end()) {
				objects.erase(it);
			}
			delete obj;
			obj = nullptr;
		}
		markedForDeletion.clear();
	}
	//gameManager.ClearedLevelCheck(); // checks if the level is completed when destroying an object
}

void Engine::AddObject(Object* o)
{
	markedForAddition.push_back(o);
}

void Engine::DeleteObject(Object* o)
{
	markedForDeletion.push_back(o);
}

PreLoader& Engine::GetPreLoader()
{
	return preLoader;
}

//LevelManager& Engine::GetLevelManager()
//{
//	return levelManager;
//}

InputManager& Engine::GetInputManager()
{
	return inputManager;
}

GameManager& Engine::GetGameManager()
{
	return gameManager;
}

CollisionManager& Engine::GetCollisionManager()
{
	return collisionManager;
}

void Engine::LoadScenes()
{
	for (const auto& entry : fs::directory_iterator(scenePath)) {
		std::string filepath = entry.path().string();

		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0))
		{
			allScenes.emplace_back(filepath);
			std::cout << "Scene found: " << filepath << "\n"; //allScenes[allScenes.size() - 1].sceneName << 
		}
	}
	gameManager.InitLevels(allScenes);
}

void Engine::ClearCurrentScene()
{
	if (objects.size() > 0) {
		markedForDeletion.insert(markedForDeletion.end(), objects.begin(), objects.end());
		objects.clear();
	}
}

void Engine::LoadScene(std::string name)
{
	//this prevents the game from loading the same scene twice, but there could be functionality to reload a scene
	Scene* newScene = GetScene(name);
	if (newScene != currentScene) {
		ClearCurrentScene();
		newScene->LoadScene();
		currentScene = newScene;
		std::cout << "Scene loaded: " << newScene->sceneName << "\n";
	}
}

void Engine::ReloadCurrentScene()
{
	ClearCurrentScene();
	currentScene->LoadScene();
	std::cout << "Scene reloaded: " << currentScene->sceneName << "\n";
}

void Engine::LoadObjectsIntoScene(std::string name)
{
	Scene* sceneToAdd = GetScene(name);
	sceneToAdd->LoadScene();
	std::cout << "Objects from scene added: " << sceneToAdd->sceneName << "\n";
}

void Engine::OpenSceneSelection()
{
	LoadScene("SceneSelect");

	sf::Vector2f basePos(750, 150);
	int margin = 50 + 10;
	for (auto& scene : allScenes) {
		Object* obj = new Object(basePos);
		obj->AddComponent<SpriteRenderer>("SceneSelectionButton", true);
		obj->AddComponent<TextRenderer>("goofy", scene.sceneName);
		obj->AddComponent<SceneSelectButton>(scene);
		basePos.y += margin;
	}
}

void Engine::OpenSceneEditor(Scene scene)
{
	{
		window->setVisible(false);
		inEditMode = true;
		SceneEditor editor(scene);
		inEditMode = false;
		window->setVisible(true);
	}
}

Scene* Engine::GetScene(std::string name)
{
	for (auto& scene : allScenes) {
		if (scene.sceneName == name) {
			return &scene;
		}
	}
}
