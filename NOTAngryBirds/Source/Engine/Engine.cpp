#include "Engine.h"
#include "Objects/Object.h"
#include "Components/Transform.h"
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
	PhysicsObject* physicsObj1 = new PhysicsObject(b2Vec2{ 0, 17.5 }, b2Vec2{ 100, 2 }, b2_staticBody);
	Transform* objTrans = new Transform();
	physicsObj1->AddComponent(objTrans);
	PhysicsObject* physicsObj2 = new PhysicsObject(b2Vec2{ 25, 15.75 }, b2Vec2{ .5, 1.5 });
	PhysicsObject* physicsObj3 = new PhysicsObject(b2Vec2{ 25, 14.25 }, b2Vec2{ .5, 1.5 });
	Grid* grid = new Grid(gameManager.GetWindow(), inputManager);
	launcherRef = new Launcher();

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

	const std::filesystem::path pathToShow{ argc >= 2 ? argv[1] : std::filesystem::current_path() };

	for (const auto& entry : std::filesystem::directory_iterator(pathToShow)) {
		const auto filenameStr = entry.path().filename().string();
		if (entry.is_directory()) {
			std::cout << "dir:  " << filenameStr << '\n';
		}
		else if (entry.is_regular_file()) {
			std::cout << "file: " << filenameStr << '\n';
		}
		else
			std::cout << "??    " << filenameStr << '\n';
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
