#pragma once

#include <vector>
#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"

class Object;
class PreLoader;
class Grid;
class Engine;


struct GameManager
{
    GameManager();

    void SetWorldId(b2WorldId* id);
    b2WorldId& GetWorldId();

    void SetWindow(sf::RenderWindow* window);
    sf::RenderWindow& GetWindow();

    Engine* enginePtr;
    PreLoader* preLoaderPtr;
    Grid* gridPtr;
    sf::RenderWindow* winPtr;
    b2WorldId* worldId;

    const int worldScale = 50; // 50 pixels to 1 meter
};