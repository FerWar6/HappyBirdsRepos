#include "PreLoader.h"
#include <filesystem>
#include <iostream>
#include "Managers/ServiceLocator.h"
namespace fs = std::filesystem;

PreLoader::PreLoader()
	: buttonFunctions()
{
	sl::SetPreLoader(this);
	std::string assetsPath = "Assets";
	std::string uiPath = "Assets/UI";
	LoadTextures(uiPath);
	LoadSpriteSheets();
	LoadFonts(assetsPath);
}

sf::Texture& PreLoader::GetTexture(std::string name)
{
	for (TextureItem& texture : GetTextureItems()) {
		std::string textureName = texture.GetName();
		size_t pos = textureName.find('_');
		if (pos != std::string::npos) {
			std::string resolutionPart = textureName.substr(pos);

			textureName.erase(pos);
		}
		if (name.compare(textureName) == 0) {
			//std::cout << "successful return of texture: " << name << std::endl;
			return texture.GetTexture();
		}
	}
	std::cout << "unsuccessful return of texture: " << name << std::endl;
}

SpriteSheet& PreLoader::GetSpriteSheet(std::string name)
{
	for (SpriteSheet& sheet : GetSpriteSheets()) {
		std::string sheetName = sheet.GetName();
		if (name.compare(sheetName) == 0) {
			return sheet;
		}
	}
	std::cout << "unsuccessful return of sprite sheet: " << name << std::endl;
}

sf::Font& PreLoader::GetFont(std::string name)
{
	for (FontItem& font : GetFontItems()) {
		std::string fontName = font.GetName();
		if (name.compare(fontName) == 0) {
			return font.GetFont();
		}
	}
	std::cout << "unsuccessful return of font: " << name << std::endl;
}

std::vector<TextureItem>& PreLoader::GetTextureItems()
{
	return textureItems;
}

std::vector<SpriteSheet>& PreLoader::GetSpriteSheets()
{
	return spriteSheets;
}

std::vector<FontItem>& PreLoader::GetFontItems()
{
	return fontItems;
}

void PreLoader::LoadTextures(std::string path)
{
	for (const auto& entry : fs::directory_iterator(path)) {
		std::string filePath = entry.path().string();

		if (filePath.size() >= 4 &&
			(filePath.compare(filePath.size() - 4, 4, ".png") == 0 ||
				filePath.compare(filePath.size() - 4, 4, ".jpg") == 0))
		{
			AddTexture(filePath);
		}
	}
}

void PreLoader::LoadSpriteSheets()
{
	for (TextureItem& texture : GetTextureItems()) {
		if (texture.IsSheet()) {
			AddSpriteSheet(texture);
		}
	}
}

void PreLoader::LoadFonts(std::string path)
{
	for (const auto& entry : fs::directory_iterator(path)) {
		std::string filePath = entry.path().string();

		if (filePath.size() >= 4 &&
			(filePath.compare(filePath.size() - 4, 4, ".ttf") == 0)) 
		{
			AddFont(filePath);
		}
	}
}

void PreLoader::AddTexture(std::string p)
{
	textureItems.emplace_back(p);
}
void PreLoader::AddSpriteSheet(TextureItem& t)
{
	spriteSheets.emplace_back(t);
}

void PreLoader::AddFont(std::string p)
{
	fontItems.emplace_back(p);
}
