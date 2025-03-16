#pragma once
#include "Objects/Components/Component.h"
#include "Engine/Scenes/Scene.h"
#include <functional>
class InputManager;

class SceneSelectButton : public Component
{
public:
	SceneSelectButton(Scene& scene);
	Scene sceneData;
	void Update() override;
	std::function<void()> OnClick; 
private:
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};