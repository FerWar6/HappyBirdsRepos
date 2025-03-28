#pragma once
#include "Datatypes/Clock.h"
#include <vector>
class Engine;
class Scene;
class Object;
class GameManager
{
public:
    // The gamemanager handles game logic 
    GameManager(Engine& eng);
    void InitLevels(std::vector<Scene>& scenes);
    void Update();
    void ClearedLevelCheck(); // Used to detect when to move onto new level
    void AddPlayerScore(int score);

    void SetLastShotTaken(bool taken);
    void OpenLevelSelection();
    void LoadNextLevel();
    void OnLevelLoaded();
    void SetLaunchedProjectile(Object* obj);
private:
    Object* launchedProjectile;
    Scene* currentLevel;
    std::vector<Scene*> levels;
    Engine& engine;
    Clock levelClock;
    bool endLevelCheck;
    int playerScore;
};
