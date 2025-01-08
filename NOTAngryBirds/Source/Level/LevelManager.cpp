#include "LevelManager.h"
#include <filesystem>
namespace fs = std::filesystem;


LevelManager::LevelManager()
{
	LoadLevels();
}

void LevelManager::LoadLevels()
{
	for (const auto& entry : fs::directory_iterator(levelsPath)) {
		std::string filePath = entry.path().string();

		if (filePath.size() >= 4 && (filePath.compare(filePath.size() - 4, 4, ".txt") == 0))
		{
			std::cout << "file found!: " << filePath << "\n";
		}
	}
}

void LevelManager::SaveLevel()
{
}

void LevelManager::AddObject(b2Vec2 pos, b2BodyType type)
{
	PhysicsObject obj = PhysicsObject(pos, b2Vec2{ 2.0, 2.0 }, type, 1);
	objs.push_back(obj);
	//objs.emplace_back(pos, b2Vec2{ 2.0, 2.0 }, type, 1);
	//objs.emplace_back(pos, b2Vec2{ 2.0, 2.0 }, type, 1);
}