#pragma once
class Engine;
class GameManager
{
public:
    GameManager(Engine& eng);
    void ClearedLevelCheck();
    void AddPlayerScore(int score);
private:
    Engine& engine;
    int playerScore;
};
