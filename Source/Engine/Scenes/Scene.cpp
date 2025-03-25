#include "Scene.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <box2d/box2d.h>

Scene::Scene(std::string& pathToScne)
	: pathToScene(pathToScne),
	sceneName(GetNameFromPath())
{
}

void Scene::SaveScene(std::vector<Object*>& objects)
{
	std::ofstream file;
	file.open(pathToScene, std::ios::out); //write to text file
	if (file.is_open()) {
		for (auto obj : objects) {
			file << obj->GetSaveData() << "\n";
		}
		file.close();
	}
	std::cout << "Scene saved: " << sceneName << "\n";
}

void Scene::LoadScene()
{
	std::ifstream file; //this is a file pointer/cursor to somewhere in the file
	file.open(pathToScene, std::ios::in); //read from text file
	if (file.is_open()) {
		//count the amount of objects in file
		std::string line;
		int amountOfObj = 0;
		while (std::getline(file, line)) { //gets a line of data from file and uses it to create an object
			new Object(line);
			amountOfObj++;
		}
		file.close();
		//file.seekg(0, std::ios::beg); // moves file cursor to the start of the file
	}
	else {
		std::cout << "could find file: " << pathToScene << "\n";
	}
}

std::string Scene::GetNameFromPath()
{
	std::string name = pathToScene;

	size_t charPos;
	charPos = name.find_last_of("/");

	if (charPos != std::string::npos) {
		name.erase(name.begin(), name.begin() + charPos + 1); //plus one to include the slash itself
	}
	
	charPos = name.find_last_of(".");
	if (charPos != std::string::npos) {
		name.erase(name.begin() + charPos, name.end());
	}

	return name;
}