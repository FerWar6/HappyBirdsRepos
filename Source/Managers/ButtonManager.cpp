#include "ButtonManager.h"
#include "Objects/Components/Button.h"
void ButtonManager::UpdateButtonCalls()
{
	for (ButtonCall& call : calls) {
		//std::cout << "button call made: " << call.layer << "\n";
		if (call.layer == EDITOR) {
			call.func();
			EraseAllCalls();
			return;
		}
	}
	for (ButtonCall& call : calls) {
		call.func();
		calls.erase(std::find(calls.begin(), calls.end(), call));
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
