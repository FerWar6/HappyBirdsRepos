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
	//levelManager.AddObject(b2Vec2{ 5.0, -5.0 }, b2_staticBody);
	levelManager.AddObject(b2Vec2{ 5.0, -10.0 }, b2_dynamicBody);
}

void Engine::Update()
{
	//std::cout << "UPDATE CALLED" << "\n";
	gameManager.UpdateObjectsVector();
	inputManager.InputCheck();
	for (auto& obj : gameManager.GetObjects()) {
		obj->Update();
	}
}

void Engine::FixedUpdate()
{
	//std::cout << "FIXEDUPDATE CALLED" << "\n";
	gameManager.UpdateObjectsVector();
	for (auto& obj : gameManager.GetObjects()) {
		//std::cout << "object pointer 1: " << gameManager.GetObjects()[0] << "\n";
		//std::cout << "object pointer 2: " << gameManager.GetObjects()[1] << "\n";
		//obj->GetSize();
		//std::cout << "size.x: " << obj->GetSize().x << "\n";
		obj->GetPos();
		obj->GetRect();
		obj->Update();
		obj->FixedUpdate();
	}
}

GameManager* Engine::GetManager()
{
	return &gameManager;
}

