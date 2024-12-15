#pragma once

#include <stdexcept>

#include "Managers/GameManager.h"

namespace ServiceLocator {
    inline GameManager* gameManager = nullptr;
    inline GameManager* GetGameManager() { return gameManager; }
    inline void SetGameManager(GameManager* dm) { gameManager = dm; }
}

namespace sl = ServiceLocator;