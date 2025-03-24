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
	bool AwakeBodiesInWorld();
private:
	std::vector<Object*>* objects;
	b2WorldId* worldId;
};

