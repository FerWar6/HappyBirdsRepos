#pragma once
#include <vector>
#include "box2d/id.h"
class Object;
struct b2WorldId;
class CollisionManager
{
public:
	CollisionManager();
	void Start();
	void UpdateCollisions();
	bool IsBodyAsleep(b2BodyId id);
	bool AllBodiesAsleep();
private:
	std::vector<Object*>* objects;
	b2WorldId* worldId;
};

