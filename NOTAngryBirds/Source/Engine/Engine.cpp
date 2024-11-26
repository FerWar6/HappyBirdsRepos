#include "Engine.h"
#include "Objects/Object.h"
Engine::Engine()
	: preLoader(),
	manager(),
	block(sf::FloatRect(100,100,100,100), preLoader.GetTexture("block"))
{
}

void Engine::Update()
{
	manager.UpdateObjectsVector();
	for (auto& obj : manager.GetObjects()) {
		obj->Update();
	}
}

void Engine::FixedUpdate()
{
	manager.UpdateObjectsVector();
	for (auto& obj : manager.GetObjects()) {
		obj->FixedUpdate();
	}
}

