#pragma once
#include "Objects/Components/Component.h"
#include <functional>
#include "Managers/ButtonFunctions.h"
class InputManager;
class LevelEditor;

class EditorItem : Component
{
public:
	EditorItem();
	void Update() override;
	std::function<void()> OnClick;
	void SetSelected(bool sel);
	void Select();
	bool HoveringOver();

private:
	LevelEditor& levelEdtr;
	InputManager& inputMan;
	bool selected;
};

