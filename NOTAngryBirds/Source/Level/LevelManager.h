#pragma once
#include "Objects/PhysicsObject.h"
class LevelManager
{
public:
	LevelManager();
	void LoadLevels();
	void SaveLevel();
	void AddObject(b2Vec2 pos, b2BodyType type);
private:
	std::vector<PhysicsObject> objs;
	//std::vector<PhysicsObject*> objs;
};