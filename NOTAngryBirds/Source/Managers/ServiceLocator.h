#pragma once
#include <stdexcept>
struct GameManager;
class PreLoader;
class Object;

namespace ServiceLocator {
    inline PreLoader* preLdr = nullptr;
    inline PreLoader* GetPreLoader() { return preLdr; }
    inline void SetPreLoader(PreLoader* pl) { preLdr = pl; }

    inline GameManager* gameManager = nullptr;
    inline GameManager* GetGameManager() { return gameManager; }
    inline void SetGameManager(GameManager* gm) { gameManager = gm; }


    // If you select an object and create a component, the component will add itself to the selected object
    // The object will automatically set itself as the selected object unless you set the paramater in its consturctor as false

    inline Object* selectedObj = nullptr;
    inline Object* GetSelectedObj() { return selectedObj; }
    inline void SetSelectedObj(Object* obj) { selectedObj = obj; }
}

namespace sl = ServiceLocator;