#include "Scene.h"
#include <iostream>
Scene::Scene(std::string& pathToScne)
	: pathToScene(pathToScne),
	sceneName(GetNameFromPath())
{
	std::cout << sceneName << "\n";
}

void Scene::SaveScene()
{

}

void Scene::LoadScene()
{
	//TODO - read the file and load all of the objects inside of the file

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