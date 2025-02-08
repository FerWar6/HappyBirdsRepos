#pragma once
#include <vector>
#include <functional>
enum ButtonLayer {
	UI,
	EDITOR
};
class Button;
struct ButtonCall {
	ButtonCall(ButtonLayer l, Button* b)
	: layer(l),
	button(b) {}

	ButtonLayer layer;
	Button* button;

	bool operator==(const ButtonCall& other) const {
	return layer == other.layer && button == other.button;
	}
};

class ButtonManager
{
public:
	ButtonManager() = default;
	void UpdateButtonCalls();
	void AddButtonCall(ButtonLayer layer, Button* button);
	void EraseAllCalls();
private:
	std::vector<ButtonCall> calls;
};

