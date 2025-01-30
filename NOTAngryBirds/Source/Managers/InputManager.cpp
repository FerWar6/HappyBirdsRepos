#include "InputManager.h"
#include "Engine/Engine.h"
#include "Managers/ServiceLocator.h"
#include "Managers/GameManager.h"
#include "DataTypes/Camera.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

InputManager::InputManager()
{
	InstantiateInputKeys();
}

void InputManager::UpdateInputs()
{
	//MSG msg = {};
	//std::cout << GetKey(MOUSE_SCRL_UP) << "\n";
	//std::cout << GetKeyState(WM_MOUSEHWHEEL) << "\n";
	//while (GetMessage(&msg, nullptr, 0, 0)) {
	//	if (msg.message == WM_MOUSEWHEEL) {
	//		// Extract wheel delta
	//		int wheelDelta = GET_WHEEL_DELTA_WPARAM(msg.wParam);

	//		// Output scroll direction
	//		if (wheelDelta > 0) {
	//			std::cout << "Mouse wheel scrolled up\n";
	//		}
	//		else {
	//			std::cout << "Mouse wheel scrolled down\n";
	//		}
	//	}

	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
	
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
	sf::Vector2i pixelPos = sf::Mouse::getPosition(win);
	mousePos = (sf::Vector2i)win.mapPixelToCoords(pixelPos);
	//std::cout << "set mousepos as " << "x: " << mousePos.x << " y:" << mousePos.y << "\n";

	//mousePos = sf::Mouse::getPosition(win);

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
	case A:
		return (GetAsyncKeyState(0x41) & 0x8000) != 0;
		break;
	case B:
		return (GetAsyncKeyState(0x42) & 0x8000) != 0;
		break;
	case C:
		return (GetAsyncKeyState(0x43) & 0x8000) != 0;
		break;
	case D:
		return (GetAsyncKeyState(0x44) & 0x8000) != 0;
		break;
	case E:
		return (GetAsyncKeyState(0x45) & 0x8000) != 0;
		break;
	case F:
		return (GetAsyncKeyState(0x46) & 0x8000) != 0;
		break;
	case G:
		return (GetAsyncKeyState(0x47) & 0x8000) != 0;
		break;
	case H:
		return (GetAsyncKeyState(0x48) & 0x8000) != 0;
		break;
	case I:
		return (GetAsyncKeyState(0x49) & 0x8000) != 0;
		break;
	case J:
		return (GetAsyncKeyState(0x4A) & 0x8000) != 0;
		break;
	case K:
		return (GetAsyncKeyState(0x4B) & 0x8000) != 0;
		break;
	case L:
		return (GetAsyncKeyState(0x4C) & 0x8000) != 0;
		break;
	case M:
		return (GetAsyncKeyState(0x4D) & 0x8000) != 0;
		break;
	case N:
		return (GetAsyncKeyState(0x4E) & 0x8000) != 0;
		break;
	case O:
		return (GetAsyncKeyState(0x4F) & 0x8000) != 0;
		break;
	case P:
		return (GetAsyncKeyState(0x50) & 0x8000) != 0;
		break;
	case Q:
		return (GetAsyncKeyState(0x51) & 0x8000) != 0;
		break;
	case R:
		return (GetAsyncKeyState(0x52) & 0x8000) != 0;
		break;
	case S:
		return (GetAsyncKeyState(0x53) & 0x8000) != 0;
		break;
	case T:
		return (GetAsyncKeyState(0x54) & 0x8000) != 0;
		break;
	case U:
		return (GetAsyncKeyState(0x55) & 0x8000) != 0;
		break;
	case V:
		return (GetAsyncKeyState(0x56) & 0x8000) != 0;
		break;
	case W:
		return (GetAsyncKeyState(0x57) & 0x8000) != 0;
		break;
	case X:
		return (GetAsyncKeyState(0x58) & 0x8000) != 0;
		break;
	case Y:
		return (GetAsyncKeyState(0x59) & 0x8000) != 0;
		break;
	case Z:
		return (GetAsyncKeyState(0x5A) & 0x8000) != 0;
		break;


	case ARROW_UP:
		return (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
	break;
	case ARROW_DOWN:
		return (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
		break;
	case ARROW_LEFT:
		return (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
		break;
	case ARROW_RIGHT:
		return (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
		break;
	case MOUSE_L:
		return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
		break;
	case MOUSE_M:
		return (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;
		break;
	case MOUSE_R:
		return (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
		break;
	case MOUSE_SCRL_UP:
		return (GetAsyncKeyState(WM_MOUSEWHEEL) & 0x8000) != 0;
		break;
	case MOUSE_SCRL_DOWN:
		return (GetAsyncKeyState(WM_MOUSEWHEEL) & 0x8000) != 0;
		break;
	case ESCAPE:
		return (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
		break;

	case CONTROL:
		return (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
		break;
	default:
		return false;
		break;
	}
}

void InputManager::SetWindow(sf::RenderWindow& win)
{
	window = &win;
}

void InputManager::InstantiateInputKeys()
{
	for (int i = 0; i < KeyCode::KEYCODE_COUNT; i++) {
		inputKeys.emplace_back((KeyCode)i);
	}
}
