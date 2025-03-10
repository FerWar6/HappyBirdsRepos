#pragma once
#include "Objects/Components/Component.h"
#include <functional>
#include "Managers/ButtonFunctions.h"
class InputManager;

class Button : public Component
{
public:
	Button(ButtFuncId function);
	void Update() override;
	std::function<void()> OnClick;
	std::string GetSaveData() override;
private:
	ButtFuncId funcId;
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};