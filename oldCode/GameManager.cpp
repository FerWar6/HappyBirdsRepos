#include "GameManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include <iostream>

void GameManager::SetWorldId(b2WorldId* id)
{
    worldId = id;
}


InputManager& GameManager::GetInputManager()
{
    return enginePtr->GetInputManager();
}

b2WorldId& GameManager::GetWorldId()
{
    return *worldId;
}
