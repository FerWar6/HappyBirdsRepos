#include "Button.h"
#include "Objects/Object.h"
#include "Managers/InputManager.h"
Button::Button(std::function<void()> onClick, InputManager& inputM)
	: Component("Button"),
    OnClick(onClick),
    inputMan(inputM),
    mousePos(inputMan.cursorPos)
{
    inputMan.onMouseLeftDown.AddListener(std::bind(&Button::HandleClick, this));
}

Button::~Button()
{
    inputMan.onMouseLeftDown.RemoveListener(std::bind(&Button::HandleClick, this));
}

void Button::HandleClick()
{
    //if inside of button and isclicking, do handleClick
    sf::Vector2i size = (sf::Vector2i)object->GetSize();
    sf::Vector2i pos = (sf::Vector2i)object->GetPos();
    if (mousePos.x > pos.x && mousePos.x < pos.x + size.x && mousePos.y > pos.y && mousePos.y < pos.y + size.y) {
        if (OnClick) OnClick();
    }
}
