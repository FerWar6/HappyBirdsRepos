#include "EditorItem.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
#include "Engine/Scenes/SceneEditor.h"

EditorItem::EditorItem()
    : Component(EDITOR_ITEM),
    inputMan(sl::GetInputManager()),
    sceneEditor(sl::GetSceneEditor()),
    OnClick(std::bind(&EditorItem::Select, this)),
    selected(false)
{}

void EditorItem::Render(sf::RenderWindow& window) 
{
    if (selected) { // Renders a white border around object when selected
        sf::RectangleShape outline(object.GetSize());
        outline.setPosition(object.GetPos());
        outline.setRotation(object.GetRot());
        outline.setOrigin(outline.getSize() / 2.f);
        outline.setFillColor(sf::Color(0, 0, 0, 0));
        outline.setOutlineThickness(-2); //size of the border
        outline.setOutlineColor(sf::Color(255, 255, 255, 255));
        window.draw(outline);
    }
}

void EditorItem::SetSelected(bool sel)
{
    selected = sel;
}

bool EditorItem::HoveringOver()
{
    sf::Vector2i s = (sf::Vector2i)object.GetSize();
    sf::Vector2i p = (sf::Vector2i)object.GetPos();
    sf::Vector2i mP = inputMan.GetMousePos();
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}

void EditorItem::Select()
{
    if (!selected) { // Deselects when selected and selects when not selected
        sceneEditor.SetSelectedObj(&object);
    }
    else {
        sceneEditor.ClearSelectedObj();
    }
}
