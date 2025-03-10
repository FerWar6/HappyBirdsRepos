#pragma once

#include "Textures/TextureItem.h"
class SpriteSheet
{
public:
	SpriteSheet(TextureItem& txrItem);
	sf::Texture& GetTexture();
	sf::Vector2i GetFrameSize();
	std::string& GetName();
	int GetNumOfFramesInAnim(int animId);
	int GetAmountOfAnimations();
	sf::Vector2i frameSize;
private:
	int GetFrameAmount(int animId);
	bool IsFrameEmpty(sf::Vector2i pos);
	sf::Texture texture;
	sf::Image sheetImg;
	std::string name;
	int amountOfAnims;
	std::vector<int> numOfFramesForEachAnim;
};

