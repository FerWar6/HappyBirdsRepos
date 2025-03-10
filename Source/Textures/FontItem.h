#pragma once
#include <string>
#include <SFML/Graphics/Font.hpp>
class FontItem {
public:
	FontItem(std::string path);
	sf::Font& GetFont();
	std::string& GetName();
private:
	sf::Font font;
	std::string name;
};