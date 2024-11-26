#pragma once

#include <vector>

class Object;

class GameManager
{
public:
    GameManager();

    void UpdateObjectsVector();
    void AddObject(Object* obj);
    void DeleteObject(Object* obj);
    std::vector<Object*>& GetObjects();
private:
    std::vector<Object*> objects;
    std::vector<Object*> markedForAddition;
    std::vector<Object*> markedForDeletion;
};