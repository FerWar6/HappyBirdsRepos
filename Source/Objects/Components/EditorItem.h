#pragma once
#include "Objects/Components/Component.h"
#include <functional>
#include "Managers/ButtonFunctions.h"
class InputManager;
class SceneEditor;

class EditorItem : public Component
{
public:
	EditorItem();
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	std::function<void()> OnClick;
	void SetSelected(bool sel);
	void Select();
	bool HoveringOver();

private:
	SceneEditor& sceneEditor;
	InputManager& inputMan;
	bool selected;
};

