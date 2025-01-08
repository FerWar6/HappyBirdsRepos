#pragma once
#include "Objects/Components/Component.h"
#include "SFML/Graphics.hpp"
struct SpriteRenderer : Component
{
	SpriteRenderer(Object& obj, sf::Texture& txrRef);
	sf::Sprite sprite;
	void Render(sf::RenderWindow& window) override;
};