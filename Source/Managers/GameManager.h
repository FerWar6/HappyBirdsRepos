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
    void OnLevelLoaded(); // called when level is loaded. resets variables
    void ClearedLevelCheck(); // Used to detect when to move onto new level
    void AddPlayerScore(int score); // Not used in end version

    void SetLastShotTaken(bool taken);
    void OpenLevelSelection();//outdated
    void LoadLevelWithIndex(); //Load level using currentLevelIndex
    void SetLaunchedProjectile(Object* obj); // Launched projectile used to move the camera when shooting
    void AddWinObject(WinConditionItem* item); 
    void DeleteWinObject(WinConditionItem* item);
    bool AllWinObjectsAlseep();
    void SetCameraPan(Object* obj); // Sets the object the camera pans to at the beginning of the level
    void InitLevels(std::vector<Scene>& scenes); // Gets all scenes that contain "level" and adds it to levels

    void SetLauncherPtr(Launcher* ptr); // Sets the launcher of the current level
private:
    Launcher* launcherPtr;
    Object* launchedProjectile; // Keeps track of the cannonball
    std::vector<WinConditionItem*> winItems; // Keeps track of the winobjects inside of the level

    int currentLevelIndex = 0;
    std::vector<Scene*> levels; // all levels in the game
    
    Engine& engine;
    Clock levelClock; // level clock keeps track of if the shoot action is over
    Clock resetLevelClock; // used to keep track of when to reset/end the level

    bool isInLevel; // only runs logic when in level
    bool wonLevel; // has player won level?
    bool lostLevel; // has player lost level?
    bool lastShotTaken; // is the last shot taken?
    int playerScore; // Not used. keeps track of the score of the player

    bool panningLevel; // Is currently panning level?
    float panTime = 3; // time to pan at beginning of level
    float panSpeed = 1.5;// speed of pan at beginning of level
    
    float followCamSpeed = 4; // speed of the camera when following cannonball

    float moveToMenuSpeed = 6; // speed when moving back to menu
};
