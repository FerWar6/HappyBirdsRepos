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
	// TODO - detect all of the scenes with "level" inside of the name
	for (auto& scene : scenes) {
		size_t pos = scene.sceneName.find('l'); // find a way to detect "level"
		//if (pos != std::string::npos) {
		//
	}
}
void GameManager::Update()
{
	if (endLevelCheck) {
		float resetTime = 1;
		if (engine.GetCollisionManager().AwakeBodiesInWorld()) {
			levelClock.Reset();
		}
		else if(levelClock.GetTimeInSeconds() > resetTime){
			engine.LoadObjectsIntoScene("EndLevelUI");
			//sl::GetEngineCore().SetPauseWorld(true);
			std::cout << "Reset Level\n";
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

void GameManager::LoadNextLevel()
{
	std::cout << "Next level loaded \n";
}

void GameManager::OnLevelLoaded()
{
	endLevelCheck = false;
}
