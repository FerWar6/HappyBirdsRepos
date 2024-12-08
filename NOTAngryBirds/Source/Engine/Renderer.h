#pragma once
#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>
#include <box2d/box2d.h>
#include "Objects/Object.h"
#include "SFML/Graphics.hpp"
#include "Managers/GameManager.h"
class Renderer
{
public:
	Renderer(sf::RenderWindow& win);
	void Render();
private:
	b2WorldDef worldDef;
	b2WorldId worldId;

	b2BodyDef groundBodyDef;
	b2ShapeDef groundShapeDef;
	b2BodyId groundId;

	b2BodyDef bodyDef;
	b2BodyId bodyId;
	b2Polygon dynamicBox;
	b2ShapeDef shapeDef;

	sf::RenderWindow& window;
	GameManager* manager;
	std::vector<Object*> objectsToRender;
};