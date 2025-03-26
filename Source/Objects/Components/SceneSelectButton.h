#pragma once
#include "Objects/Components/Component.h"
#include "Engine/Scenes/Scene.h"
#include <functional>
class InputManager;

class SceneSelectButton : public Component
{
	// Scene select button is creates specifically for choosing a scene for the scene editor
public:
	SceneSelectButton(Scene& scene);
	Scene& sceneData; // copy of the data in the scene
	void Update() override;
	std::function<void()> OnClick; 
private:
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};