#include "Button.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"

Button::Button(ButtFuncId function)
    : Component(BUTTON),
    funcId(function),
    OnClick(sl::GetPreLoader()->buttonFunctions.GetButtonFunction(function)),
    inputMan(sl::GetGameManager()->GetInputManager())
{}
void Button::Update()
{
    if (inputMan.GetKeyDown(MOUSE_L)) HandleClick();
    //bool to check if there is a sprite renderer
    // set the color of the spriterenderer if you have it
    if (object->HasComponent(ComponentType::SPRITE_RENDERER)) {
        SpriteRenderer* renPtr = (SpriteRenderer*)object->GetComponent(ComponentType::SPRITE_RENDERER);
        if (HoveringOver() && inputMan.GetKey(KeyCode::MOUSE_L)) {
            renPtr->sprite.setColor(sf::Color(200, 200, 200));
        }
        else if (HoveringOver()) {
            renPtr->sprite.setColor(sf::Color(255, 255, 255));
        }
        else {
            renPtr->sprite.setColor(sf::Color(220, 220, 220));
        }
    }
}


void Button::HandleClick()
{
    if (OnClick && HoveringOver()) {
        OnClick();
    }
}

bool Button::HoveringOver()
{
    sf::Vector2i s = (sf::Vector2i)object->GetSize();
    sf::Vector2i p = (sf::Vector2i)object->GetPos();
    sf::Vector2i mP = inputMan.mousePos;
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}

std::string Button::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(funcId) + " ";
    std::cout << data << "\n";
    return data;
}