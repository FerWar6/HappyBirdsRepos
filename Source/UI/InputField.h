#pragma once
#include "SFML/Graphics.hpp"
class InputManager;
class InputField
{
	// the inputfield is a WIP
public:
	InputField(std::string newTxt, sf::Vector2f pos);
	void Update();
	void Render(sf::RenderWindow& window);

	std::string& GetText();
	void SetText(std::string& newTxt);
private:
	bool selected;
	InputManager& inputMan;
	sf::Text text;
	bool HoveringOver();
};
