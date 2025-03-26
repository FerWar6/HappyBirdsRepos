#pragma once
#include "Objects/Components/Component.h"
#include "SFML/Graphics.hpp"

class TextRenderer : public Component
{
public:
	TextRenderer(std::string fontName, std::string textContent);

	void Render(sf::RenderWindow& window) override;
	std::string GetSaveData() override;
private:
	sf::Text text;
	std::string fontName;
};