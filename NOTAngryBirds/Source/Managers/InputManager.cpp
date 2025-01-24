#include "InputManager.h"
#include "Engine/Engine.h"
#include "Managers/ServiceLocator.h"
#include "Managers/GameManager.h"
#include <windows.h>
#include <iostream>

InputManager::InputManager()
{
	InstantiateInputKeys();
}

void InputManager::UpdateInputs()
{
	MSG msg = {};
	//std::cout << "Scroll the mouse wheel to see messages...\n";

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (msg.message == WM_MOUSEWHEEL) {
			// Extract wheel delta
			int wheelDelta = GET_WHEEL_DELTA_WPARAM(msg.wParam);

			// Output scroll direction
			if (wheelDelta > 0) {
				std::cout << "Mouse wheel scrolled up\n";
			}
			else {
				std::cout << "Mouse wheel scrolled down\n";
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	for (auto& input : inputKeys) {
		if (GetKey(input.keyCode)) {
			if (input.state == UP_IDLE) {
				input.state = DOWN;
			}
			else {
				input.state = DOWN_IDLE;
			}
		}
		else {
			if (input.state == DOWN_IDLE || input.state == DOWN) {
				input.state = UP;
			}
			else {
				input.state = UP_IDLE;
			}
		}
	}
}

void InputManager::SetMousePos(sf::RenderWindow& win)
{
	mousePos = sf::Mouse::getPosition(win);
}

bool InputManager::GetKeyDown(KeyCode key)
{
	for (auto& input : inputKeys) {
		if (input.keyCode == key && input.state == DOWN) return true;
	}
	return false;
}

bool InputManager::GetKeyUp(KeyCode key)
{
	for (auto& input : inputKeys) {
		if (input.keyCode == key && input.state == UP) return true;
	}
	return false;
}

bool InputManager::GetKey(KeyCode key)
{
	switch (key) {
	case MOUSE_L:
		return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
		break;

	case MOUSE_M:
		return (GetKeyState(VK_MBUTTON) & 0x8000) != 0;

		break;
	case MOUSE_R:
		return (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
		break;
	default:
		return false;
		break;
	}
}

void InputManager::InstantiateInputKeys()
{
	for (int i = 0; i < KeyCode::KEYCODE_COUNT; i++) {
		inputKeys.emplace_back((KeyCode)i);
	}
}

