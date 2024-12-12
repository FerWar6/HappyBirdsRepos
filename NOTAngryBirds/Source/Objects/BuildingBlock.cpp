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
	//physics calculations here
}

void BuildingBlock::Render(sf::RenderWindow& window)
{
	sprite.setPosition(GetPos());
	window.draw(sprite);
}
