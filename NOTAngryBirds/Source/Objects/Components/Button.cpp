#include "Button.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
Button::Button(std::function<void()> onClick)
	: Component(ComponentType::BUTTON),
    OnClick(onClick),
    inputMan(sl::GetGameManager()->GetInputManager())
{
    inputMan.onMouseLeftDown.AddListener(std::bind(&Button::HandleClick, this));
}

Button::~Button()
{
    inputMan.onMouseLeftDown.RemoveListener(std::bind(&Button::HandleClick, this));
}

void Button::Update()
{
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
    if (OnClick && HoveringOver()) OnClick();
}

bool Button::HoveringOver()
{
    sf::Vector2i s = (sf::Vector2i)object->GetSize();
    sf::Vector2i p = (sf::Vector2i)object->GetPos();
    sf::Vector2i mP = inputMan.mousePos;
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}
