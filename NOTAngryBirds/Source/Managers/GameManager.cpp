#include "GameManager.h"
#include "Managers/ServiceLocator.h"
#include <iostream>
GameManager::GameManager()
{
	sl::SetGameManager(this);
}

void GameManager::UpdateObjectsVector()
{

    if (!markedForAddition.empty()) {
        objects.insert(objects.end(), markedForAddition.begin(), markedForAddition.end());
        //std::cout << "first in markedforaddition: " << markedForAddition[0].GetSize().x << std::endl;
        markedForAddition.clear();
    }
    if (!markedForDeletion.empty()) {
        for (Object* obj : markedForDeletion) {
            auto it = std::find(objects.begin(), objects.end(), obj);
            if (it != objects.end()) {
                objects.erase(it);
            }
            delete obj;
            obj = nullptr;
        }
        markedForDeletion.clear();
    }
    //std::cout << objects.size() << "\n";
}

void GameManager::AddObject(Object* obj)
{
    markedForAddition.push_back(obj);
}

void GameManager::DeleteObject(Object* obj)
{
    markedForDeletion.push_back(obj);
}

std::vector<Object*>& GameManager::GetObjects()
{
    return objects;
}

void GameManager::SetWorldId(b2WorldId* id)
{
    worldId = id;
}

b2WorldId& GameManager::GetWorldId()
{
    return *worldId;
}
