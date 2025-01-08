#include "Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Engine::Engine()
	: preLoader(),
	gameManager(),
	levelManager(),
	inputManager(this)
{
	gameManager.enginePtr = this;
}

void Engine::Start()
{
	Grid* grid = new Grid(gameManager.GetWindow(), inputManager);
	launcherPtr = new Launcher();
	{
		Object* obj = new Object();
		RectRigidbody* body = new RectRigidbody(*obj, b2Vec2{ 0, 17.5 }, b2Vec2{ 100, 2 }, b2_staticBody, 1, gameManager.GetWorldId());
		obj->AddComponent(body);
		sf::Texture& txr = preLoader.GetTexture("BoxPlaceholder");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);
	}
	{
		Object* obj = new Object();
		RectRigidbody* body = new RectRigidbody(*obj, b2Vec2{ 0, 17.5 }, b2Vec2{ 2, 30 }, b2_staticBody, 1, gameManager.GetWorldId());
		obj->AddComponent(body);
		sf::Texture& txr = preLoader.GetTexture("BoxPlaceholder");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);
	}
	{
		Object* obj = new Object();
		RectRigidbody* body = new RectRigidbody(*obj, b2Vec2{ 30, 17.5 }, b2Vec2{ 2, 30 }, b2_staticBody, 1, gameManager.GetWorldId());
		obj->AddComponent(body);
		sf::Texture& txr = preLoader.GetTexture("BoxPlaceholder");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);
	}



	{
		Object* obj = new Object();

		RectRigidbody* body = new RectRigidbody(*obj, b2Vec2{ 25, 15.75 }, b2Vec2{ .5, 1.5 }, b2_dynamicBody, 1, gameManager.GetWorldId());
		obj->AddComponent(body);

		sf::Texture& txr = preLoader.GetTexture("BoxPlaceholder");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);
	}
	{
		Object* obj = new Object();

		RectRigidbody* body = new RectRigidbody(*obj, b2Vec2{ 25, 14.25 }, b2Vec2{ 1, 1.5 }, b2_dynamicBody, 1, gameManager.GetWorldId());
		obj->AddComponent(body);

		sf::Texture& txr = preLoader.GetTexture("BoxPlaceholder");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);
	}



	{
		Object* obj = new Object();

		CircleRigidbody* body = new CircleRigidbody(*obj, b2Vec2{ 15, 5 }, 1, b2_dynamicBody, gameManager.GetWorldId());
		obj->AddComponent(body);

		sf::Texture& txr = preLoader.GetTexture("CannonBall");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);
	}
	std::string levelsPath = "Assets/Levels/";
	int levelNum = 1;

	std::ofstream MyFile(levelsPath + "level" + std::to_string(levelNum) + ".txt");

	// Write to the file
	MyFile << "Files can be tricky, but it is fun enough! \n";

	MyFile.close();

	std::string myText;

	std::ifstream MyReadFile("Assets/Levels/level1.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file
		std::cout << myText;
	}
	// Close the file
	MyReadFile.close();
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
