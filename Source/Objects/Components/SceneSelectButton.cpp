#include "SceneSelectButton.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
SceneSelectButton::SceneSelectButton(Scene& scene)
    : Component(BASE), // add scene select button to enum if needed for getcomponent functionality
    sceneData(scene),
    OnClick([&]() { sl::GetEngine().OpenSceneEditor(sceneData); }),
    inputMan(sl::GetInputManager())
{}

void SceneSelectButton::Update()
{
    if (inputMan.GetKeyDown(MOUSE_L)) HandleClick();
    if (object.HasComponent(ComponentType::SPRITE_RENDERER)) { // Greys out sprite when hovering over and clicking on
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

void SceneSelectButton::HandleClick()
{
    if (OnClick && HoveringOver()) {
        OnClick();
    }
}

bool SceneSelectButton::HoveringOver()
{
    sf::Vector2i s = (sf::Vector2i)object.GetSize();
    sf::Vector2i p = (sf::Vector2i)object.GetPos();
    sf::Vector2i mP = inputMan.GetMousePos();
    return mP.x > p.x - s.x / 2 && mP.x < p.x + s.x / 2 && mP.y > p.y - s.y / 2 && mP.y < p.y + s.y / 2;
}
