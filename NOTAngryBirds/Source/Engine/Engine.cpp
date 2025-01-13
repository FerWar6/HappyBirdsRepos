#include "Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/Button.h"
#include "Managers/ServiceLocator.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Engine::Engine()
	: preLoader(),
	gameManager(),
	levelManager(),
	inputManager(this),
	currentScene(Scene::MainMenu)
{
	gameManager.enginePtr = this;
}

void Engine::Start()
{
	std::string path = "Assets/Levels/level1.txt";
	//levelManager.SaveExistingLevel(path, objects);
	levelManager.LoadLevel(path);
	Grid* grid = new Grid(gameManager.GetWindow(), inputManager);
	launcherPtr = new Launcher();
	{
		Object* obj = new Object();
		obj->SetPos(600,600);
		SpriteRenderer* ren = new SpriteRenderer("StartButton");
		Button* butt = new Button(std::bind(&Engine::MoveToScene, this, Scene::Level));
	}
}

void Engine::Update()
{
	inputManager.InputCheck();
	for (auto& obj : objects) {
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
	objects.push_back(p);
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

void Engine::MoveToScene(Scene scene)
{
	std::cout << "clicked on button\n";
}
