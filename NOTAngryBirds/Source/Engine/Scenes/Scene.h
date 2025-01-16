#pragma once
#include <string>
struct Scene
{
	//engine constructs every scene file in a folder and loads all of the propperties
	//the scene contains a vector of objects
	Scene(std::string& pathToScene);
	std::string pathToScene;
	std::string sceneName;
	void SaveScene();
	void LoadScene();
	std::string GetNameFromPath();
};