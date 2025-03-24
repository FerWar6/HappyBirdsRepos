#include "GameManager.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
GameManager::GameManager(Engine& eng)
	: playerScore(0),
	engine(eng)
{}

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
