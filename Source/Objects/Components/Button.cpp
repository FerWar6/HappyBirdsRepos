#include "Button.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"

Button::Button(ButtFuncId function)
    : Component(BUTTON),
    funcId(function),
    OnClick(sl::GetPreLoader().buttonFunctions.GetButtonFunction(function)),
    inputMan(sl::GetInputManager())
{}
void Button::Update()
{
    if (!active) return;
    if (inputMan.GetKeyDown(MOUSE_L) && HoveringOver()) HandleClick(); // Do button function if player clicked on button
    if (object.HasComponent(ComponentType::SPRITE_RENDERER)) {
        SpriteRenderer* renPtr = (SpriteRenderer*)object.GetComponent(ComponentType::SPRITE_RENDERER);
        if (HoveringOver() && inputMan.GetKey(KeyCode::MOUSE_L)) {
            renPtr->SetColor(sf::Color(200, 200, 200));
        }
        else if (HoveringOver()) {
            renPtr->SetColor(sf::Color(255, 255, 255));
        }
        else {
            renPtr->SetColor(sf::Color(220, 220, 220));
        }
    }
}

void Button::HandleClick()
{
    if (OnClick) { // Check if OnClick is not a nullptr
        inputMan.buttonMan.AddButtonCall(GAME_UI, OnClick); // Adds a buttonCall to the buttonManager
    }
}

bool Button::HoveringOver() // Returns true if mouse is inside of the bounds of the button
{
    sf::Vector2i s = (sf::Vector2i)object.GetSize();
    sf::Vector2i p = (sf::Vector2i)object.GetPos();
    sf::Vector2i mP = inputMan.GetMousePos();
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}

std::string Button::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(funcId) + " ";
    return data;
}