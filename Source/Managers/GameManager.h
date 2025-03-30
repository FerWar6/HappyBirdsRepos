#pragma once
#include "Datatypes/Clock.h"
#include <vector>
class Engine;
class Scene;
class Object;
class WinConditionItem;
class Launcher;
class GameManager
{
public:
    // The gamemanager handles game logic 
    GameManager(Engine& eng);
    void Update();
    void FixedUpdate();
    void OnLevelLoaded();
    void ClearedLevelCheck(); // Used to detect when to move onto new level
    void AddPlayerScore(int score);

    void SetLastShotTaken(bool taken);
    void OpenLevelSelection();
    void LoadLevelWithIndex();
    void SetLaunchedProjectile(Object* obj);
    void AddWinObject(WinConditionItem* item);
    void DeleteWinObject(WinConditionItem* item);
    bool AllWinObjectsAlseep();
    void SetCameraPan(Object* obj);
    void InitLevels(std::vector<Scene>& scenes);

    void SetLauncherPtr(Launcher* ptr);
private:
    Launcher* launcherPtr;
    Object* launchedProjectile;
    std::vector<WinConditionItem*> winItems;

    int currentLevelIndex = 0;
    std::vector<Scene*> levels;
    
    Engine& engine;
    Clock levelClock;
    Clock resetLevelClock;

    bool isInLevel;
    bool wonLevel;
    bool lostLevel;
    bool lastShotTaken;
    int playerScore;

    bool panningLevel;
    float panTime = 3;
    float panSpeed = 1.5;
    
    float followCamSpeed = 4;

    float moveToMenuSpeed = 6;
};
