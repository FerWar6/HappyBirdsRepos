#include "Engine.h"
#include "Objects/Object.h"
#include <iostream>
Engine::Engine()
	:	gameManager()
{}

void Engine::Start()
{
	//allObjects.emplace_back(b2Vec2{ 5.0, -10.0 }, b2Vec2{ 2.0, 2.0 }, b2_dynamicBody, 1);
	PhysicsObject obj1(b2Vec2{ 5.0, -10.0 }, b2Vec2{ 2.0, 2.0 }, b2_dynamicBody, 1);
	PhysicsObject obj2(b2Vec2{ 5.0, -10.0 }, b2Vec2{ 2.0, 2.0 }, b2_dynamicBody, 1);
	PhysicsObject obj3(b2Vec2{ 5.0, -10.0 }, b2Vec2{ 2.0, 2.0 }, b2_dynamicBody, 1);
	PhysicsObject obj4(b2Vec2{ 5.0, -10.0 }, b2Vec2{ 2.0, 2.0 }, b2_dynamicBody, 1);
	allObjects.push_back(obj1);
	allObjects.push_back(obj2);
	allObjects.push_back(obj3);
	allObjects.push_back(obj4);
}

void Engine::Update()
{
	//std::cout << "UPDATE CALLED" << "\n";
	gameManager.UpdateObjectsVector();
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

