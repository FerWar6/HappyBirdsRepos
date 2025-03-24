#pragma once
#include <string>
#include <vector>
class Object;
class Scene
{
public:
	Scene(std::string& pathToScne);
	std::string pathToScene;
	std::string sceneName;
	void SaveScene(std::vector<Object*>& objects);
	void LoadScene();
private:
	std::string GetNameFromPath();
};