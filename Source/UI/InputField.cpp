#include "InputField.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
#include "Managers/InputManager.h"
#include <iostream>;
InputField::InputField(std::string newTxt, sf::Vector2f pos)
    :  inputMan(sl::GetInputManager()),
    selected(false)
{
    text.setFont(sl::GetPreLoader().GetFont("goofy"));
    text.setCharacterSize(200);
    text.setPosition(sf::Vector2f(-100, -100));
    text.setString(newTxt);
    text.setOrigin(text.getLocalBounds().getSize() / 2.f);
}
void InputField::Update()
{
    if (inputMan.GetKeyDown(MOUSE_L) && HoveringOver()) {
        selected = !selected;
    }
    if (selected) {
        text.setString(inputMan.GetTextInput());
    }
    //std::cout << "text size: " << inputMan.GetTextInput() << "\n";
    //std::cout << "text: " << inputMan.GetTextInput() << "\n";
}
void InputField::Render(sf::RenderWindow& window)
{
    // TODO - make text blue when selected
    sf::RectangleShape outline(text.getGlobalBounds().getSize());
    outline.setPosition(text.getGlobalBounds().getPosition());
    outline.setOrigin(outline.getSize() / 2.f);
    sf::Color fillCol = HoveringOver() ? sf::Color(255, 255, 255, 155) : sf::Color(255, 255, 255, 100);
    outline.setFillColor(fillCol);
    //outline.setOutlineThickness(3);
    //outline.setOutlineColor(fillCol);
    //window.draw(outline);
    sf::FloatRect localBounds = text.getLocalBounds();
    sf::FloatRect globalBounds = text.getGlobalBounds();


    sf::RectangleShape localRect(sf::Vector2f(localBounds.width, localBounds.height));
    localRect.setPosition(text.getPosition().x + localBounds.left, text.getPosition().y + localBounds.top);
    localRect.setFillColor(sf::Color::Transparent);
    localRect.setOutlineColor(sf::Color::Green);
    localRect.setOutlineThickness(2);

    // Create a rectangle for GLOBAL bounds (with transformations)
    sf::RectangleShape globalRect(sf::Vector2f(globalBounds.width, globalBounds.height));
    globalRect.setPosition(globalBounds.left, globalBounds.top);
    globalRect.setFillColor(sf::Color::Transparent);
    globalRect.setOutlineColor(sf::Color::Red);
    globalRect.setOutlineThickness(2);

    window.draw(localRect);  // Green: Local Bounds
    window.draw(globalRect); // Red: Global Bounds
    window.draw(text);
}

std::string& InputField::GetText()
{
	return (std::string)text.getString();
}

void InputField::SetText(std::string& newTxt)
{
    // TODO - recenter text when resizing
	text.setString(newTxt);
}

bool InputField::HoveringOver()
{
    // TODO - implement this into the other button HoveringOver functions
    sf::Vector2i mP = inputMan.GetMousePos();
    return text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mP));
}
