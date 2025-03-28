#pragma once
#include "Datatypes/Clock.h"
#include <vector>
class Engine;
class Scene;
class Object;
class Launcher;
class GameManager
{
public:
    // The gamemanager handles game logic 
    GameManager(Engine& eng);
    void Update();
    void OnLevelLoaded();
    void ClearedLevelCheck(); // Used to detect when to move onto new level
    void AddPlayerScore(int score);

    void SetLastShotTaken(bool taken);
    void OpenLevelSelection();
    void LoadNextLevel();
    void SetLaunchedProjectile(Object* obj);
    void AddWinObject(Object* obj);
    bool AllWinObjectsAlseep();
    void SetCameraPan(Object* obj);
    void InitLevels(std::vector<Scene>& scenes);

    void SetLauncherPtr(Launcher* ptr);
private:
    Launcher* launcherPtr;
    Object* launchedProjectile;
    std::vector<Object*> winObjects;
    Scene* currentLevel;
    std::vector<Scene*> levels;
    Engine& engine;
    Clock levelClock;
    bool endLevelCheck;
    int playerScore;


    bool panningLevel;
    float panTime = 3;
    float panSpeed = 1;
    
    float followCamSpeed = 3;
};
