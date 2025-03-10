#pragma once
#include "UI/UIElement.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <functional>
class InputManager;
class Object;
class Hierarchy : UIElement
{
public:
	Hierarchy();
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	std::function<void()> OnClick;
private:
	void UpdateObjTxt();
	void UpdateObjTxtVec();
	bool HoveringOver(sf::Vector2i s, sf::Vector2i p);
	int GetHoverPos();

	sf::Text titleTxt;
	std::vector<sf::Text> objectsTxts;
	InputManager& inputMan;
	std::vector<Object*>& objects;
};