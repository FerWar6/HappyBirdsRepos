#include "Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/Button.h"
#include "Objects/Components/Launcher.h"
#include "Managers/ServiceLocator.h"
#include "Level/LevelEditor.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

Engine::Engine()
	: preLoader(),
	gameManager(),
	levelManager(),
	inputManager(),
	currentScene(nullptr)
{
	gameManager.enginePtr = this;
	LevelEditor* editorPtr = nullptr;
	preLoader.buttonFunctions.LinkButtonFunctions(this, editorPtr);

	bool editorMode = false;
	if (editorMode) {
		LevelEditor editor(inputManager, editorPtr);
	}
}

void Engine::Start()
{
	LoadScenes();
	LoadScene("MainMenu");
	//std::string path = "Assets/Levels/level1.txt";
	//levelManager.LoadLevel(path);
	//levelManager.SaveExistingLevel(path, objects);
	//Grid* grid = new Grid(gameManager.GetWindow(), inputManager);
	//{
	//	new Object(sf::Vector2f(150, 700), 90, sf::Vector2f(600, 600));
	//	sf::Vector2f scale(1.5, 1.5);
	//	SpriteRenderer* ren = new SpriteRenderer("LauncherStand", scale, sf::Vector2f(25, 6));
	//	ren->lockRotation = true;
	//	new SpriteRenderer("Launcher", scale, sf::Vector2f(13, 87));
	//	new Launcher("PreviewDot");
	//}
	//{
	//	Object* obj = new Object(sf::Vector2f(150, 150));
	//	new SpriteRenderer("LevelSelectButton", true);
	//	new Button(ButtFuncId::MOVE_TO_SCENE);
	//	std::cout << obj->GetSaveData() << "\n";
	//}
}

void Engine::Update()
{
	inputManager.SetMousePos(gameManager.GetWindow());
	inputManager.UpdateInputs();
	for (auto obj : objects) {
		obj->Update();
	}
}

void Engine::FixedUpdate()
{
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
}

GameManager* Engine::GetManager()
{
	return &gameManager;
}

void Engine::AddObject(Object* p)
{
	markedForAddition.push_back(p);
}

void Engine::DeleteObject(Object* o)
{
	markedForDeletion.push_back(o);
}

GameManager& Engine::GetGameManager()
{
	return gameManager;
}

PreLoader& Engine::GetPreLoader()
{
	return preLoader;
}

LevelManager& Engine::GetLevelManager()
{
	return levelManager;
}

InputManager& Engine::GetInputManager()
{
	return inputManager;
}

void Engine::LoadScenes()
{
	for (const auto& entry : fs::directory_iterator(scenePath)) {
		std::string filepath = entry.path().string();

		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0))
		{
			allScenes.emplace_back(filepath);
			std::cout << "file found!: " << filepath << "\n";
		}
	}
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
