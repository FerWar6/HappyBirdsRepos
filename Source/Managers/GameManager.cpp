#include "GameManager.h"
#include "Engine/Engine.h"
#include "Engine/EngineCore.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
#include "Managers/ServiceLocator.h"
GameManager::GameManager(Engine& eng)
	: playerScore(0),
	engine(eng),
	levelClock(),
	resetLevelClock(),
	wonLevel(false),
	lostLevel(false),
	isInLevel(false),
	lastShotTaken(false),
	launchedProjectile(nullptr),
	launcherPtr(nullptr)
{}

void GameManager::Update()
{
	if (sl::GetInputManager().GetKeyDown(ARROW_LEFT) && isInLevel) {
		currentLevelIndex--;
		LoadLevelWithIndex();
	}
	if (sl::GetInputManager().GetKeyDown(ARROW_RIGHT) && isInLevel) {
		currentLevelIndex++;
		LoadLevelWithIndex();
	}
}


void GameManager::FixedUpdate()
{
	//std::cout << "in level: " << isInLevel << "\n";
	if (!isInLevel) return;
	//std::cout << "win objects alseep: " << AllWinObjectsAlseep() << "  amount of winObjects: " << winItems.size() << "\n";
	if (panningLevel)
	{
		if (levelClock.GetTimeInSeconds() > panTime) {
			sl::GetRenderer().GetCamera().SetFollowObject(nullptr);
			if (launcherPtr) launcherPtr->active = true;
			sl::GetRenderer().GetCamera().SetCamSpeed(followCamSpeed);
			panningLevel = false;
		}
		return;
	}
	if (!wonLevel) {
		resetLevelClock.Reset();
		wonLevel = winItems.size() == 0;
	}
	else if (wonLevel) {
		launcherPtr->active = false;
		float lingerOnLevelTime = 3;
		if (resetLevelClock.GetTimeInSeconds() > lingerOnLevelTime) {
			sl::GetRenderer().GetCamera().SetCamSpeed(moveToMenuSpeed);
			sl::GetRenderer().GetCamera().SetFollowObject(nullptr);
			if (sl::GetRenderer().GetCamera().ReachedTarget()) {
				engine.LoadObjectsIntoScene("WonLevelUI");
				wonLevel = false;
				launchedProjectile = nullptr;
				isInLevel = false;
				currentLevelIndex++;
			}
		}
	}
	if (launchedProjectile && launchedProjectile->HasComponent(CIRCLE_RIGIDBODY)) {
		launcherPtr->active = false;
		float resetTime = 1.5;
		b2BodyId& bodyId = ((CircleRigidbody*)launchedProjectile->GetComponent(CIRCLE_RIGIDBODY))->GetBodyId();
		//std::cout << "IsAsleep " << engine.GetCollisionManager().IsBodyAsleep(bodyId) << "\n";
		if (!engine.GetCollisionManager().IsBodyAsleep(bodyId) || !AllWinObjectsAlseep()) {
			levelClock.Reset();
		}
		else if (levelClock.GetTimeInSeconds() > resetTime) {
			launchedProjectile = nullptr;
			if (!wonLevel && lastShotTaken) {
				lostLevel = true;
			}
			else {
				sl::GetRenderer().GetCamera().SetFollowObject(nullptr);
				launcherPtr->active = true;
			}
		}
	}
	if (lostLevel) {
		sl::GetRenderer().GetCamera().SetFollowObject(nullptr);
		sl::GetRenderer().GetCamera().SetCamSpeed(moveToMenuSpeed);
		if (sl::GetRenderer().GetCamera().ReachedTarget()) {
			engine.LoadObjectsIntoScene("LostLevelUI");
			wonLevel = false;
			lostLevel = false;
			lastShotTaken = false;
			isInLevel = false;
		}
	}
	//delay for second before moving to menu
}

void GameManager::OnLevelLoaded()
{
	if (sl::GetRenderer().GetCamera().GetFollowObject()) {
		panningLevel = true;
		sl::GetRenderer().GetCamera().SetCamSpeed(panSpeed);
	}
	wonLevel = false;
	lastShotTaken = false;
	if (launcherPtr) launcherPtr->active = false;
	isInLevel = true;
	resetLevelClock.Reset();
	levelClock.Reset();

	//pan the camera, wait for amout of seconds and pan back
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
	lastShotTaken = taken;
}

void GameManager::OpenLevelSelection() //outdated
{
	engine.LoadScene("level1");
	OnLevelLoaded();
}

void GameManager::LoadLevelWithIndex() //uses the current level index and loads it
{
	if (currentLevelIndex > 0 && currentLevelIndex >= levels.size()) { // checks if there are any more levels to play
		engine.LoadScene("ThankYouForPlaying");
		currentLevelIndex = 0;
		return;
	}
	if (currentLevelIndex == -1) currentLevelIndex = 0;
	engine.LoadScene(levels[currentLevelIndex]->sceneName);
	OnLevelLoaded();
}

void GameManager::SetLaunchedProjectile(Object* obj)
{
	launchedProjectile = obj;
}

void GameManager::AddWinObject(WinConditionItem* item)
{
	winItems.push_back(item);
}

void GameManager::DeleteWinObject(WinConditionItem* item)
{
	auto it = std::find(winItems.begin(), winItems.end(), item);
	if (it != winItems.end()) {
		winItems.erase(it);
	}
}

bool GameManager::AllWinObjectsAlseep()
{
	for (WinConditionItem* winItem : winItems) {
		if (winItem) {
			if (winItem->IsMoving()) return false;
		}
	}
	return true;
}

void GameManager::SetCameraPan(Object* obj)
{
	sl::GetRenderer().GetCamera().SetFollowObject(obj);
}

void GameManager::InitLevels(std::vector<Scene>& scenes)
{
	for (auto& scene : scenes) {
		if (scene.sceneName.find("level") != std::string::npos) { // returns true if "level" is inside of the string sceneName
			levels.push_back(&scene);
			std::cout << "Level found: " << scene.sceneName << "\n";
		}
	}
}

void GameManager::SetLauncherPtr(Launcher* ptr)
{
	launcherPtr = ptr;
}