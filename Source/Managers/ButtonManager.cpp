#include "ButtonManager.h"
#include "Objects/Components/Button.h"
void ButtonManager::UpdateButtonCalls()
{
	for (ButtonCall& call : calls) {
		if (call.layer == EDITOR) {
			call.button->OnClick();
			EraseAllCalls();
			return;
		}
		call.button->OnClick();
		calls.erase(std::find(calls.begin(), calls.end(), call));
	}
}

void ButtonManager::AddButtonCall(ButtonLayer layer, Button* button)
{
	ButtonCall call(layer, button);
	calls.push_back(call);
}

void ButtonManager::EraseAllCalls()
{
	calls.clear();
	//for (auto& call : calls) {
	//	calls.erase(call);
	//}
}
