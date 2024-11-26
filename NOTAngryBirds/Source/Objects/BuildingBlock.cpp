#include "BuildingBlock.h"
#include <iostream>
BuildingBlock::BuildingBlock(sf::FloatRect rect, sf::Texture& txr)
	: Object(rect),
	texture(txr)
{
	sprite.setTexture(texture);
}

void BuildingBlock::FixedUpdate()
{
}

void BuildingBlock::Render(sf::RenderWindow& window)
{
	std::cout << "rendering block" << std::endl;
	sprite.setPosition(GetPos());
	window.draw(sprite);
}
