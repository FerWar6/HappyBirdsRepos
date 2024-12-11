#pragma once
#include "Objects/PhysicsObject.h"
class LevelManager
{
public:
	LevelManager();
	void AddObject(b2BodyType type);
private:
	std::vector<PhysicsObject> objs;
};

