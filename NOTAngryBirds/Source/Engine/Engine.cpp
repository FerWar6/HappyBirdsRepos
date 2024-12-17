#include "Engine.h"
#include "Objects/Object.h"
#include <iostream>
Engine::Engine()
	: preLoader(),
	gameManager(),
	levelManager(),
	inputManager()
{
	inputManager.levelManager = &levelManager;
}

void Engine::Start()
{
	gameObjects.push_back(std::make_unique<PhysicsObject>(b2Vec2{ 5.0, -10.0 }, b2Vec2{ 2.0, 2.0 }, b2_dynamicBody, 1));
	gameObjects.push_back(std::make_unique<PhysicsObject>(b2Vec2{ 7.0, -5.0 }, b2Vec2{ 1.0, 1.0 }, b2_dynamicBody, 1));
	gameObjects.push_back(std::make_unique<PhysicsObject>(b2Vec2{ 0, -20.0 }, b2Vec2{ 10, 2.0 }, b2_staticBody, 1));
}

void Engine::Update()
{
	gameManager.UpdateObjectsVector();
	inputManager.InputCheck();
	for (auto& obj : gameObjects) {
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