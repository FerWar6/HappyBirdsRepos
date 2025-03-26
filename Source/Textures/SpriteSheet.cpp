#include "SpriteSheet.h"
#include <iostream>
SpriteSheet::SpriteSheet(TextureItem& txrItem)
	: texture(txrItem.GetTexture()),
	frameSize(txrItem.GetSize()),
	name(txrItem.GetName()),
    sheetImg(texture.copyToImage())
{
    //remove extention from name
	amountOfAnims = texture.getSize().y / frameSize.y;

	for (unsigned int i = 0; i < amountOfAnims; ++i) {
		int numOfFrames = GetFrameAmount(i);
		numOfFramesForEachAnim.emplace_back(numOfFrames);
	}
    std::cout << "Successfully created spritesheet from: " << name << "\n";

}

int SpriteSheet::GetNumOfFramesInAnim(int animId)
{
	if (animId <= amountOfAnims) {
		return numOfFramesForEachAnim[animId - 1];
	}
	else {
        std::cout << "not enough animations in this spritesheet" << "\n";
	}
}
int SpriteSheet::GetAmountOfAnimations()
{
    return amountOfAnims;
}
int SpriteSheet::GetFrameAmount(int animId)
{
    sf::Vector2u textureSize = texture.getSize();

    int amountOfFrames = 0;
    sf::Vector2i searchPos = sf::Vector2i(0, (animId) * frameSize.y);
    for (int i = 0; i < texture.getSize().x / frameSize.x; ++i) {
        if (IsFrameEmpty(searchPos)) return amountOfFrames;
        else {
            searchPos.x += frameSize.x;
            amountOfFrames++;
        }
    }
}
bool SpriteSheet::IsFrameEmpty(sf::Vector2i pos) // returns true if any pixels are found
{
    int startX = std::max(0, pos.x);
    int startY = std::max(0, pos.y);
    int endX = std::min(pos.x + frameSize.x, static_cast<int>(texture.getSize().x));
    int endY = std::min(pos.y + frameSize.y, static_cast<int>(texture.getSize().y));

    for (int x = startX; x < endX; x += 2) { // checks in steps of 2 to make it faster
        for (int y = startY; y < endY; y += 2) {
            sf::Color color = sheetImg.getPixel(x, y);

            if (color.a != 0) {
                return false;
            }
        }
    }

    return true;
}
sf::Texture& SpriteSheet::GetTexture()
{
    return texture;
}

sf::Vector2i SpriteSheet::GetFrameSize()
{
    return frameSize;
}


std::string& SpriteSheet::GetName()
{
    return name;
}
