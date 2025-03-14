#include "Renderer.h"
#include "Managers/ServiceLocator.h"
#include <cmath>
#define PI 3.14159265358979323846

Renderer::Renderer(std::vector<Object*>& objRef)
    : gameObjectsRef(objRef)
{
    int winWidth = 1500;
    int winHeight = 900;
    std::string windowName = "Happy Birds";
    window.create(sf::VideoMode(winWidth, winHeight), windowName);
    sl::SetWindow(&window);
}

void Renderer::Start()
{
    //window.setSize({ 100, 100 });
}
void Renderer::Render()
{
    window.clear();
    for (auto& obj : gameObjectsRef) {
        obj->Render(window);
    }
    window.display();
}

sf::RenderWindow& Renderer::GetWindow()
{
    return window;
}
