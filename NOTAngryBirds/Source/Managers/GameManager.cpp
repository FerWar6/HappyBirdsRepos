#include "GameManager.h"
#include "Managers/ServiceLocator.h"
GameManager::GameManager()
{
	sl::SetGameManager(this);
}

void GameManager::UpdateObjectsVector()
{
    if (!markedForAddition.empty()) {
        objects.insert(objects.end(), markedForAddition.begin(), markedForAddition.end());
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
}

void GameManager::AddObject(Object* obj)
{
	objects.push_back(obj);
}

void GameManager::DeleteObject(Object* obj)
{
	objects.push_back(obj);
}

std::vector<Object*>& GameManager::GetObjects()
{
    return objects;
}
