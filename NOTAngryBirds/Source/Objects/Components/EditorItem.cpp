#include "EditorItem.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
#include "Level/LevelEditor.h"

EditorItem::EditorItem()
    : Component(EDITOR_ITEM),
    inputMan(sl::GetGameManager()->GetInputManager()),
    levelEdtr(*sl::GetLevelEditor()),
    selected(false)
{
}

void EditorItem::Update()
{
    if (inputMan.GetKeyDown(MOUSE_L) && HoveringOver()) 
    {
        if (!selected) {
            levelEdtr.SetSelectedObj(object);
        }
        else {
            levelEdtr.ClearSelectedObj();
        }
    }
    bool hasRen = object->HasComponent(SPRITE_RENDERER);
    if (selected) {
        ((SpriteRenderer*)object->GetComponent(SPRITE_RENDERER))->sprite.setColor(sf::Color(200, 200, 200));
    }
    else {
        ((SpriteRenderer*)object->GetComponent(SPRITE_RENDERER))->sprite.setColor(sf::Color(255, 255, 255));
    }
}

void EditorItem::SetSelected(bool sel)
{
    selected = sel;
}


bool EditorItem::HoveringOver()
{
    sf::Vector2i s = (sf::Vector2i)object->GetSize();
    sf::Vector2i p = (sf::Vector2i)object->GetPos();
    sf::Vector2i mP = inputMan.mousePos;
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}