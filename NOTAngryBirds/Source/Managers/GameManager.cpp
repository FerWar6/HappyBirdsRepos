#include "GameManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include <iostream>
GameManager::GameManager()
{
	sl::SetGameManager(this);
}


void GameManager::SetWorldId(b2WorldId* id)
{
    worldId = id;
}

void GameManager::SetWindow(sf::RenderWindow* w)
{
    winPtr = w;
}

sf::RenderWindow& GameManager::GetWindow()
{
    return *winPtr;
}

b2WorldId& GameManager::GetWorldId()
{
    return *worldId;
}
