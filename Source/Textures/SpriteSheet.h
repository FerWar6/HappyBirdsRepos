#pragma once

#include "Textures/TextureItem.h"
class SpriteSheet
{
	// Detects spritesheet automatically and calculates the amount of frames and framsize
	// Spritesheet needs to have the syntax "spriteName_10x10.png"
public:
	SpriteSheet(TextureItem& txrItem);
	sf::Texture& GetTexture();
	sf::Vector2i GetFrameSize();
	std::string& GetName();
	int GetNumOfFramesInAnim(int animId);
	int GetAmountOfAnimations();
	sf::Vector2i frameSize;
private:
	int GetFrameAmount(int animId); // Calculates amount of frames on spritesheet
	bool IsFrameEmpty(sf::Vector2i pos); // returns true if any pixels are found
	sf::Texture texture;
	sf::Image sheetImg;
	std::string name;
	int amountOfAnims;
	std::vector<int> numOfFramesForEachAnim;
};

