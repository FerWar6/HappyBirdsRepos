#pragma once

#include <vector>
#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"

class Object;
class PreLoader;
class Grid;

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

    void SetWindow(sf::RenderWindow* window);
    sf::RenderWindow& GetWindow();

    PreLoader* preLoaderPtr;
    Grid* gridPtr;
    const int worldScale = 50; // 50 pixels to 1 meter
private:
    sf::RenderWindow* winPtr;
    b2WorldId* worldId;
    std::vector<Object*> objects;
    std::vector<Object*> markedForAddition;
    std::vector<Object*> markedForDeletion;
    //std::vector<T> allObjects;
};