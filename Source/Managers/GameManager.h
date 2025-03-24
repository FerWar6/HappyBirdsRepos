#pragma once
#include "Datatypes/Clock.h"
class Engine;
class Scene;
class GameManager
{
public:
    GameManager(Engine& eng);
    void Update();
    void ClearedLevelCheck();
    void AddPlayerScore(int score);

    void SetLastShotTaken(bool taken);
    void LoadNextLevel();
    void OnLevelLoaded();
private:
    Scene* currentLevel;
    Engine& engine;
    Clock levelClock;
    bool endLevelCheck;
    int playerScore;
};
