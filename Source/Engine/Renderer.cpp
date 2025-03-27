#include "Renderer.h"
#include "Managers/ServiceLocator.h"

Renderer::Renderer(std::vector<Object*>& objRef)
    : objects(objRef),
    camera()
{
    sl::SetRenderer(this);
    int winWidth = 1500;
    int winHeight = 900;
    std::string windowName = "Castle Clash";
    window.create(sf::VideoMode(winWidth, winHeight), windowName);
    camera.SetView(window);
    sl::SetWindow(&window);
}

void Renderer::Start()
{
    //window.setSize({ 100, 100 });
}
void Renderer::Render()
{
    window.clear();
    window.setView(camera.GetView());
    camera.MoveToTarget();
    for (auto& obj : objects) { // Render all objects in scene
        obj->Render(window);
    }
    window.display();
}

sf::RenderWindow& Renderer::GetWindow()
{
    return window;
}

Camera& Renderer::GetCamera()
{
    return camera;
}
