#pragma once
#include "Objects/Components/Component.h"
#include <functional>

class InputManager;
struct Button : public Component
{
	Button(std::function<void()> onClick);
	~Button();
	void Update() override;
	std::function<void()> OnClick;
private:
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};