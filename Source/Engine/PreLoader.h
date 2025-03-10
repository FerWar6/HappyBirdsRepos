#pragma once
#include <SFML/Graphics.hpp>

#include "Textures/TextureItem.h"
#include "Textures/SpriteSheet.h"
#include "Textures/FontItem.h"
#include "Managers/ButtonFunctions.h"
class PreLoader
{
public:
	PreLoader();
	sf::Texture& GetTexture(std::string name);
	SpriteSheet& GetSpriteSheet(std::string name);
	sf::Font& GetFont(std::string name);
	std::vector<TextureItem>& GetTextureItems();
	std::vector<SpriteSheet>& GetSpriteSheets();
	std::vector<FontItem>& GetFontItems();
	
	ButtonFunctions buttonFunctions;
private:
	void LoadTextures(std::string path);
	void LoadSpriteSheets();
	void LoadFonts(std::string path);

	void AddTexture(std::string path);
	void AddSpriteSheet(TextureItem& txrItem);
	void AddFont(std::string path);

	std::vector<TextureItem> textureItems;
	std::vector<SpriteSheet> spriteSheets;
	std::vector<FontItem> fontItems;
};