#pragma once
#include "Objects/Components/Component.h"
#include <functional>
#include "Managers/ButtonFunctions.h"
class InputManager;

struct Button : public Component
{
	Button(ButtFuncId function);
	~Button();
	void Update() override;
	std::function<void()> OnClick;
	std::string GetSaveData() override;
private:
	ButtFuncId funcId;
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};