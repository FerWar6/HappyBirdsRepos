#include "InputField.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
#include "Managers/InputManager.h"
#include <iostream>;
InputField::InputField(std::string newTxt)
    :  inputMan(sl::GetInputManager())
{
    text.setFont(sl::GetPreLoader().GetFont("goofy"));
    text.setCharacterSize(50);
    text.setPosition(sf::Vector2f(0, 0)); //dont forget to edit this when making UI move with camera
    text.setString(newTxt);
    text.setOrigin(text.getLocalBounds().getSize() / 2.f);
    std::cout << "size x: " << text.getGlobalBounds().getSize().x << "\n";
    std::cout << "size y: " << text.getGlobalBounds().getSize().y << "\n";
}
void InputField::Update()
{
    //std::cout << "hoveriing over: " << HoveringOver() << "\n";
}
void InputField::Render(sf::RenderWindow& window)
{

    sf::RectangleShape outline(text.getGlobalBounds().getSize());
    outline.setPosition(text.getGlobalBounds().getPosition());
    outline.setOrigin(outline.getSize() / 2.f);
    sf::Color fillCol = HoveringOver() ? sf::Color(255, 255, 255, 155) : sf::Color(255, 255, 255, 100);
    outline.setFillColor(fillCol);
    //outline.setOutlineThickness(3);
    //outline.setOutlineColor(fillCol);
    window.draw(outline);
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
    sf::Vector2i s = (sf::Vector2i)text.getGlobalBounds().getSize();
    sf::Vector2i p = (sf::Vector2i)text.getGlobalBounds().getPosition();
    sf::Vector2i mP = inputMan.GetMousePos();
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}
