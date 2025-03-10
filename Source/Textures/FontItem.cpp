#include "FontItem.h"
#include <iostream>
FontItem::FontItem(std::string p)
{
    if (font.loadFromFile(p)) {
        name = p.substr(p.find_last_of("/\\") + 1);
        size_t dotPos = name.find_last_of('.');
        if (dotPos != std::string::npos) {
            name = name.substr(0, dotPos);
        }
        std::cout << "Successfully loaded font: " << p << "\n";
    }
    else {
        std::cout << "Failed to load font: " << p << "\n";
    }
}

sf::Font& FontItem::GetFont()
{
	return font;
}

std::string& FontItem::GetName()
{
	return name;
}
