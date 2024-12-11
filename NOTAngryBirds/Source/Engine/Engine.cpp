#include "Engine.h"
#include "Objects/Object.h"
#include <iostream>
Engine::Engine()
	: preLoader(),
	gameManager(),
	levelManager()
{}

void Engine::Start()
{
	levelManager.AddObject(b2_staticBody);
	levelManager.AddObject(b2_dynamicBody);
}

void Engine::Update()
{
	std::cout << "UPDATE CALLED" << "\n";
	gameManager.UpdateObjectsVector();
	for (auto& obj : gameManager.GetObjects()) {
		obj->Update();
	}
}

void Engine::FixedUpdate()
{
	std::cout << "FIXEDUPDATE CALLED" << "\n";
	gameManager.UpdateObjectsVector();
	std::cout << "objects size: " << gameManager.GetObjects().size() << "\n";
	std::cout << "objects 1: " << gameManager.GetObjects()[0]->GetPos().y << "\n";
	for (auto& obj : gameManager.GetObjects()) {
		std::cout << "object pos: " << obj->GetPos().x << " , " << obj->GetPos().y << "\n";
		std::cout << "object size: " << obj->GetSize().x << " , " << obj->GetSize().y << "\n";
		obj->FixedUpdate();
	}
}

GameManager* Engine::GetManager()
{
	return &gameManager;
}

