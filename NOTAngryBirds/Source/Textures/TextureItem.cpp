#include "TextureItem.h"
#include <iostream>
#include <filesystem>
TextureItem::TextureItem(std::string p)
{
    if (texture.loadFromFile(p)) {
        name = p.substr(p.find_last_of("/\\") + 1);
        size_t dotPos = name.find_last_of('.');
        if (dotPos != std::string::npos) {
            name = name.substr(0, dotPos);
        }


        std::string filename = std::filesystem::path(p).filename().string();
        size_t pos = filename.find('_'); // Find the underscore separating name and resolution
        if (pos != std::string::npos) {
            std::string resolutionPart = filename.substr(pos + 1); // Extract the part after '_'

            size_t xPos = resolutionPart.find('x'); // Look for the 'x' in the resolution
            if (xPos != std::string::npos) {
                int width = std::stoi(resolutionPart.substr(0, xPos)); // Extract width
                int height = std::stoi(resolutionPart.substr(xPos + 1)); // Extract height
                frameSize = sf::Vector2i(width, height);

                size_t pos = name.find('_');
                if (pos != std::string::npos) {
                    std::string resolutionPart = name.substr(pos);

                    name.erase(pos);
                }
            }
        }
        std::cout << "Successfully loaded texture: " << p << std::endl;

        frameSize = GetFrameSize(p);
    }
    else {
        std::cout << "Failed to load texture: " << p << std::endl;
    }
    isSheet = texture.getSize().y > frameSize.y && frameSize != sf::Vector2i(0,0);
}

sf::Texture& TextureItem::GetTexture()
{
	return texture;
}

std::string& TextureItem::GetName()
{
	return name;
}

sf::Vector2i TextureItem::GetSize()
{
    return frameSize;
}

bool TextureItem::IsSheet()
{
    return isSheet;
}

sf::Vector2i TextureItem::GetFrameSize(std::string fileName)
{
    size_t pos = fileName.find('_'); // Find the underscore separating name and resolution
    if (pos != std::string::npos) {
        std::string resolutionPart = fileName.substr(pos + 1); // Extract the part after '_'

        size_t xPos = resolutionPart.find('x'); // Look for the 'x' in the resolution
        if (xPos != std::string::npos) {
            int width = std::stoi(resolutionPart.substr(0, xPos)); // Extract width
            int height = std::stoi(resolutionPart.substr(xPos + 1)); // Extract height
            return sf::Vector2i(width, height); // Return as sf::Vector2i
        }
    }

    // If no resolution in the filename, load the texture and return its height
    sf::Texture texture;
    if (texture.loadFromFile(fileName)) {
        return sf::Vector2i(texture.getSize().y, texture.getSize().y); // Return width and height of the texture
    }

    // Debug message for when the texture cannot be loaded
    std::cout << "Failed to load texture from file: " << fileName << std::endl;

    return sf::Vector2i(0, 0); // Return (0, 0) if the texture cannot be loaded or no resolution found
}

