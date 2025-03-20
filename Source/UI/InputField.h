#pragma once
#include "SFML/Graphics.hpp"
class InputManager;
class InputField
{
public:
	InputField(std::string newTxt);
	void Update();
	void Render(sf::RenderWindow& window);

	std::string& GetText();
	void SetText(std::string& newTxt);
private:
	InputManager& inputMan;
	sf::Text text;
	bool HoveringOver();
};
