#include "Engine.h"
#include "Objects/Object.h"
#include <iostream>
Engine::Engine()
	: preLoader(),
	gameManager(),
	levelManager(),
	inputManager(this)
{
}

void Engine::Start()
{
	gameObjects.push_back(std::make_unique<PhysicsObject>(b2Vec2{ 0, 17.5 }, b2Vec2{ 100, 2 }, b2_staticBody));
	Grid* grid = new Grid(gameManager.GetWindow(), inputManager);
}

void Engine::Update()
{
	gameManager.UpdateObjectsVector();
	inputManager.InputCheck();
	for (auto& obj : gameObjects) {
		obj->Update();
	}
	for (auto& obj : gameManager.GetObjects()) {
		obj->Update();
	}
}

void Engine::FixedUpdate()
{
	gameManager.UpdateObjectsVector();
	for (auto& obj : gameObjects) {
		obj->FixedUpdate();
	}
}

GameManager* Engine::GetManager()
{
	return &gameManager;
}

std::vector<std::unique_ptr<Object>>& Engine::GetGameObjects()
{
	return gameObjects;
}