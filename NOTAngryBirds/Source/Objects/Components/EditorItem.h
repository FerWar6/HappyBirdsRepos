#pragma once
#include "Objects/Components/Component.h"
#include <functional>
#include "Managers/ButtonFunctions.h"
class InputManager;
class LevelEditor;

struct EditorItem : Component
{
	EditorItem();
	void Update() override;
	std::function<void()> OnClick;
	void SetSelected(bool sel);
private:
	LevelEditor& levelEdtr;
	InputManager& inputMan;
	bool HoveringOver();
	bool selected;
};

