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
	endLevelCheck(false),
	launchedProjectile(nullptr),
	launcherPtr(nullptr)
{}


void GameManager::Update()
{
	if (panningLevel)
	{
		if (levelClock.GetTimeInSeconds() > panTime) {
			sl::GetRenderer().GetCamera().SetFollowObject(nullptr);
			if (launcherPtr) launcherPtr->active = true;
			panningLevel = false;
		}
		return;
	}

	winObjects.erase(std::remove(winObjects.begin(), winObjects.end(), nullptr), winObjects.end()); // remove nullptrs from winObjects
	//std::cout << AllWinObjectsAlseep() << " all winobjects asleep\n";
	if (launchedProjectile) {
		float resetTime = 1;
		b2BodyId& bodyId = ((CircleRigidbody*)launchedProjectile->GetComponent(CIRCLE_RIGIDBODY))->GetBodyId();
		//std::cout << "IsAsleep " << engine.GetCollisionManager().IsBodyAsleep(bodyId) << "\n";
		if (!engine.GetCollisionManager().IsBodyAsleep(bodyId)) {
			levelClock.Reset();
		}
		else if (levelClock.GetTimeInSeconds() > resetTime) {
			launchedProjectile = nullptr;
			sl::GetRenderer().GetCamera().SetFollowObject(nullptr);
		}
	}
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

void GameManager::OnLevelLoaded()
{
	panningLevel = true;
	sl::GetRenderer().GetCamera().SetCamSpeed(panSpeed);
	if (launcherPtr) launcherPtr->active = false;
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
	levelClock.Reset();
	endLevelCheck = taken;
}

void GameManager::OpenLevelSelection()
{
	engine.LoadScene("level1");
	OnLevelLoaded();
}

void GameManager::LoadNextLevel() // Cycles trough the indeces of levels to load next level
{
	int newIndex = 1;
	Scene* newLevel = levels[newIndex];
	engine.LoadScene(newLevel->sceneName);
	currentLevel = newLevel;
}


void GameManager::SetLaunchedProjectile(Object* obj)
{
	launchedProjectile = obj;
}

void GameManager::AddWinObject(Object* obj)
{
	winObjects.push_back(obj);
}

bool GameManager::AllWinObjectsAlseep()
{
	for (Object* obj : winObjects) {
		if (obj) {
			b2BodyId& bodyId = ((CircleRigidbody*)obj->GetComponent(CIRCLE_RIGIDBODY))->GetBodyId();
			if (!engine.GetCollisionManager().IsBodyAsleep(bodyId)) {
				return false;
			}
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
