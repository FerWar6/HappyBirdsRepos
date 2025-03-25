#include "ButtonManager.h"
#include "Objects/Components/Button.h"
void ButtonManager::UpdateButtonCalls() // Calls the button functions
{
	for (ButtonCall& call : calls) {
		if (call.layer == EDITOR) {
			call.func();
			EraseAllCalls();
			return;
		}
	}
	for (ButtonCall& call : calls) {
		if (call.layer == EDITOR_UI) {
			call.func();
			EraseAllCalls();
			return;
		}
	}
	for (ButtonCall& call : calls) {
		if (call.layer == GAME_UI) {
			call.func();
			EraseAllCalls();
			return;
		}
	}
}

void ButtonManager::AddButtonCall(ButtonLayer layer, std::function<void()>& onClick)
{
	ButtonCall call(layer, onClick);
	calls.push_back(call);
}

void ButtonManager::EraseAllCalls()
{
	calls.clear();
}
