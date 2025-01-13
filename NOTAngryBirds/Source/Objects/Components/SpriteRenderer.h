#pragma once
#include "Objects/Components/Component.h"
#include "SFML/Graphics.hpp"
struct SpriteRenderer : Component
{
	SpriteRenderer(std::string txrName);
	sf::Sprite sprite;

	void Render(sf::RenderWindow& window) override;
	Component* GetComponentPtr() override;

	std::string txrName; //for now this is the name of the texture because of how I set up the preloader
	//if preloader ever changes and it requires a path to the texture this will also have to change
};