#pragma once
#include <vector>

class Object;
struct b2WorldId;
class CollisionManager
{
public:
	CollisionManager();
	void Start();
	void UpdateCollisions();
	bool AllBodiesAsleep();
private:
	std::vector<Object*>* objects;
	b2WorldId* worldId;
};

