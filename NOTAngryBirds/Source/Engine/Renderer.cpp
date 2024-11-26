#include "Renderer.h"
#include "Managers/ServiceLocator.h"
Renderer::Renderer(sf::RenderWindow& win)
	: manager(sl::GetGameManager()),
	window(win)
{
}

void Renderer::Render()
{
	window.clear();
	objectsToRender = manager->GetObjects();
	for (auto& obj : objectsToRender) {
		obj->Render(window);
	}
	window.display();
}