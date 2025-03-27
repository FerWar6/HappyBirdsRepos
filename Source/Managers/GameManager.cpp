#include "GameManager.h"
#include "Engine/Engine.h"
#include "Engine/EngineCore.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
GameManager::GameManager(Engine& eng)
	: playerScore(0),
	engine(eng),
	levelClock(),
	endLevelCheck(false)
{}
void GameManager::InitLevels(std::vector<Scene>& scenes)
{
	for (auto& scene : scenes) {
		if (scene.sceneName.find("level") != std::string::npos) { // returns true if "level" is inside of the string sceneName
			levels.push_back(&scene);
			std::cout << "Level found: " << scene.sceneName << "\n";
		}
	}
}
void GameManager::Update()
{
	if (endLevelCheck) {
		float resetTime = 2; // Amount of seconds it takes for level to reset after all bodies are asleep
		if (!engine.GetCollisionManager().AllBodiesAsleep()) {
			levelClock.Reset();
		}
		else if(levelClock.GetTimeInSeconds() > resetTime){
			engine.LoadObjectsIntoScene("EndLevelUI");
			//std::cout << "Reset Level\n";
			endLevelCheck = false;
		}
	}
}

void GameManager::ClearedLevelCheck()
{
	for (auto& obj : engine.objects) {
		if (obj->HasComponent(WINCONDITION_ITEM)) return;
	}
	engine.ReloadCurrentScene();
}

void GameManager::AddPlayerScore(int score)
{
	playerScore += score;
}
void GameManager::SetLastShotTaken(bool taken)
{
	levelClock.Reset();
	endLevelCheck = taken;
}

void GameManager::OpenLevelSelection()
{
	engine.LoadScene("level1");
}

void GameManager::LoadNextLevel() // Cycles trough the indeces of levels to load next level
{
	int newIndex = 1;
	Scene* newLevel = levels[newIndex];
	engine.LoadScene(newLevel->sceneName);
	currentLevel = newLevel;
}

void GameManager::OnLevelLoaded()
{
	endLevelCheck = false;
}
