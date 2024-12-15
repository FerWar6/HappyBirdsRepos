#pragma once

#include <vector>
#include <box2d/box2d.h>

class Object;

class GameManager
{
public:
    GameManager();

    void UpdateObjectsVector();
    void AddObject(Object* obj);
    void DeleteObject(Object* obj);
    std::vector<Object*>& GetObjects();
    void SetWorldId(b2WorldId* id);
    b2WorldId& GetWorldId();
    const int worldScale = 50; // 50 pixels to 1 meter
private:
    b2WorldId* worldId;
    std::vector<Object*> objects;
    std::vector<Object*> markedForAddition;
    std::vector<Object*> markedForDeletion;
};