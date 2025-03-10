#pragma once
#include <string>
struct Scene
{
	Scene(std::string& pathToScne);
	std::string pathToScene;
	std::string sceneName;
	void SaveScene();
	void LoadScene();
	std::string GetNameFromPath();
};