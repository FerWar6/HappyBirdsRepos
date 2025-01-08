#include "PreLoader.h"
#include <filesystem>
#include <iostream>
#include "Managers/ServiceLocator.h"

namespace fs = std::filesystem;

PreLoader::PreLoader()
{
	sl::GetGameManager()->preLoaderPtr = this;
	std::string uiPath = "Assets/UI";
	LoadTextures(uiPath);
	LoadSpriteSheets();
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

std::vector<TextureItem>& PreLoader::GetTextureItems()
{
	return textureItems;
}

std::vector<SpriteSheet>& PreLoader::GetSpriteSheets()
{
	return spriteSheets;
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

void PreLoader::AddTexture(std::string p)
{
	textureItems.emplace_back(p);
}
void PreLoader::AddSpriteSheet(TextureItem& t)
{
	spriteSheets.emplace_back(t);
}
