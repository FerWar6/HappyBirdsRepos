#include "LevelManager.h"

LevelManager::LevelManager()
{}

void LevelManager::AddObject(b2BodyType type)
{
	objs.emplace_back(b2Vec2{ 5, 5 }, b2Vec2{ 2.0, 2.0 }, type, 1);
}