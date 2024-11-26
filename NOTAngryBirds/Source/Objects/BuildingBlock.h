#pragma once
#include "Objects/Object.h"
class BuildingBlock : Object
{
public:
	BuildingBlock(sf::FloatRect rect, sf::Texture& txr);
	void FixedUpdate() override;
	void Render(sf::RenderWindow& window) override;

private:
	sf::Texture& texture;
	sf::Sprite sprite;
};

