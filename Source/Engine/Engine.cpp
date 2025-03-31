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
	preLoader.buttonFunctions.LinkButtonFunctions(this, &gameManager); // Links button functions. this is used for objects to keep functionality after being stored as text
	LoadScenes(); // Loads all of the scenes inside of scenePath into allScenes
}

void Engine::Start()
{
	collisionManager.Start();
	window = &sl::GetWindow();

	LoadScene("MainMenu");
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
	gameManager.FixedUpdate();
	for (auto& obj : objects) {
		obj->FixedUpdate();
	}
}

void Engine::UpdateObjectsVector()
{
	// Adds or deletes objects before updating them to prevent nullrefex
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

void Engine::AddObject(Object* o)
{
	markedForAddition.push_back(o);
}

void Engine::DeleteObject(Object* o)
{
	// This is a check to prevent the same object from being deleted twice and breaking the code
	for (auto objPtr : markedForDeletion) {
		if (objPtr == o) {
			return;
		}
	}
	markedForDeletion.push_back(o);
}

PreLoader& Engine::GetPreLoader()
{
	return preLoader;
}

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

		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0)) // Adds all text files as scenes inside of allScenes
		{
			allScenes.emplace_back(filepath);
			std::cout << "Scene found: " << filepath << "\n";
		}
	}
	gameManager.InitLevels(allScenes);
}

void Engine::ClearCurrentScene() // Marks all object inside scene for deletion
{
	if (objects.size() > 0) {
		markedForDeletion.insert(markedForDeletion.end(), objects.begin(), objects.end());
		objects.clear();
	}
}

void Engine::LoadScene(std::string name)
{
	Scene* newScene = GetScene(name);
	ClearCurrentScene();
	newScene->LoadScene();
	currentScene = newScene;
	std::cout << "Scene loaded: " << newScene->sceneName << "\n";
}

void Engine::ReloadCurrentScene()
{
	ClearCurrentScene();
	currentScene->LoadScene();
	std::cout << "Scene reloaded: " << currentScene->sceneName << "\n";
}

void Engine::LoadObjectsIntoScene(std::string name) // Load objects into the current scene without clearing the current scene
{
	Scene* sceneToAdd = GetScene(name);
	sceneToAdd->LoadScene();
	std::cout << "Objects from scene added: " << sceneToAdd->sceneName << "\n";
}

void Engine::OpenSceneSelection() // Opens scene selection menu
{
	LoadScene("SceneSelect");

	sf::Vector2f basePos(750, 150);
	int margin = 50 - 5;
	for (auto& scene : allScenes) {
		Object* obj = new Object(basePos);
		obj->AddComponent<SpriteRenderer>("SceneSelectionButton", true);
		obj->AddComponent<TextRenderer>("goofy", scene.sceneName);
		obj->AddComponent<SceneSelectButton>(scene);
		basePos.y += margin;
	}
}

void Engine::OpenSceneEditor(Scene scene) // Turns off engine window and opens scene editor
{
	window->setVisible(false);
	inEditMode = true;
	SceneEditor editor(scene);
	inEditMode = false;
	window->setVisible(true);
}

void Engine::Quit()
{
	(*window).close();
}

Scene* Engine::GetScene(std::string name)
{
	for (auto& scene : allScenes) {
		if (scene.sceneName == name) {
			return &scene;
		}
	}
	std::cout << "Scene not found: " << name << "\n";
	return nullptr;
}
