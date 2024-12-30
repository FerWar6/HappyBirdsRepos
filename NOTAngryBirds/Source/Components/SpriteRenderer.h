#pragma once
#include "Components/Component.h"
#include "SFML/Graphics.hpp"
struct SpriteRenderer : Component
{
	SpriteRenderer();
	sf::Sprite sprite;
};