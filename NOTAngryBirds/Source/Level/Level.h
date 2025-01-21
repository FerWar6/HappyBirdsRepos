#pragma once
#include <string>
#include <vector>
class Object;
struct Level {
	Level(std::string& pathToScene);
	std::string pathToLevel;
	std::string levelName;
	void SaveLevel();
	void LoadLevel();
	void LoadLevel(std::vector<Object*>& objects);
	std::string GetNameFromPath();
};