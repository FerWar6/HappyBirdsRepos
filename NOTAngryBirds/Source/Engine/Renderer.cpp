#include "Renderer.h"
#include "Managers/ServiceLocator.h"
#include <cmath>
#define PI 3.14159265358979323846

Renderer::Renderer(std::vector<Object*>& objRef)
    : gameObjectsRef(objRef)
{}


void Renderer::Start()
{
    window = &sl::GetWindow();
}
void Renderer::Render()
{
    window->clear();
    for (auto& obj : gameObjectsRef) {
        obj->Render(*window);
    }
    window->display();
}