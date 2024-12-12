#pragma once
#include <SFML/Graphics.hpp>

#include "Textures/TextureItem.h"
#include "Textures/SpriteSheet.h"
class PreLoader
{
public:
	PreLoader();
	sf::Texture& GetTexture(std::string name);
	SpriteSheet& GetSpriteSheet(std::string name);
	std::vector<TextureItem>& GetTextureItems();
	std::vector<SpriteSheet>& GetSpriteSheets();
private:
	void LoadTextures(std::string path);
	void LoadSpriteSheets();
	void AddTexture(std::string path);
	void AddSpriteSheet(TextureItem& txrItem);

	std::vector<TextureItem> textureItems;
	std::vector<SpriteSheet> spriteSheets;
};