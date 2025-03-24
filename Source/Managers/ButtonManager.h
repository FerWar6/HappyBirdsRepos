#pragma once
#include <vector>
#include <functional>
enum ButtonLayer {
	GAME_UI,
	EDITOR_UI,
	EDITOR,
};
class Button;
struct ButtonCall {
	ButtonCall(ButtonLayer l, std::function<void()>& onClick)
	: layer(l),
	func(onClick) {}

	ButtonLayer layer;
	std::function<void()> func;

	bool operator==(const ButtonCall& other) const {
		return layer == other.layer;
	}
};

class ButtonManager
{
public:
	ButtonManager() = default;
	void UpdateButtonCalls();
	void AddButtonCall(ButtonLayer layer, std::function<void()>& onClick);
	void EraseAllCalls();
private:
	std::vector<ButtonCall> calls;
};

