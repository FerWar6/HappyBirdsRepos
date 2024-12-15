#include "LevelManager.h"

LevelManager::LevelManager()
{}

void LevelManager::AddObject(b2Vec2 pos, b2BodyType type)
{
	PhysicsObject obj = PhysicsObject(pos, b2Vec2{ 2.0, 2.0 }, type, 1);
	//objs.push_back(obj);
	//objs.emplace_back(pos, b2Vec2{ 2.0, 2.0 }, type, 1);
	//objs.emplace_back(pos, b2Vec2{ 2.0, 2.0 }, type, 1);
}