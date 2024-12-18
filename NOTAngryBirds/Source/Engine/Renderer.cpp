#include "Renderer.h"
#include "Managers/ServiceLocator.h"
#include <cmath>
#define PI 3.14159265358979323846

Renderer::Renderer(sf::RenderWindow& win, std::vector<std::unique_ptr<Object>>& objRef)
    : manager(sl::GetGameManager()),
    window(win),
    gameObjectsRef(objRef)
{}


void Renderer::Start()
{
}
void Renderer::Render()
{
    window.clear();
    for (auto& obj : manager->GetObjects()) {
        obj->Render(window);
    }
    for (auto& obj : gameObjectsRef) {
        obj->Render(window);
    }

    window.display();
}