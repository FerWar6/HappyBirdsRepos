#pragma once
#include <box2d/box2d.h>
#include <iostream>
#include <vector>
class Object;
class LevelManager
{
public:
	LevelManager();
	void LoadLevels();
	void SaveExistingLevel(std::string& lvlPath, std::vector<Object*> lvlObjs);
	void SaveNewLevel(std::vector<Object*> lvlObjs);

	void LoadLevel(std::string& lvlPath);
private:
	std::string objId = "obj";
	std::string compsId = "cps";

	std::string levelsPath = "Assets/Levels/";
	std::string ObjToTxt(Object& obj);

	std::string AddToSring(float num);
	std::string AddToSring(int num);
	std::string AddToSring(std::string string);
	//std::vector<PhysicsObject*> objs;
};