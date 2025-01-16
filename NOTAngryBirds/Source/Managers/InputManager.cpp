#include "InputManager.h"
#include "Engine/Engine.h"

#include <windows.h>
#include <iostream>

InputManager::InputManager(Engine* e)
	: enginePtr(e),
	mouseLeftClicked(false),
	mouseRightClicked(false)
{}

void InputManager::InputCheck()
{
	mousePos = sf::Mouse::getPosition(enginePtr->GetManager()->GetWindow());

	//mouse left
	if (GetKey(KeyCode::MOUSE_L) && !mouseLeftClicked) {
		onMouseLeftDown.Invoke();
		mouseLeftClicked = true;
	}
	else if (!GetKey(KeyCode::MOUSE_L) && mouseLeftClicked) {
		onMouseLeftUp.Invoke();
		mouseLeftClicked = false;
	}
	//mouse right
	if (GetKey(KeyCode::MOUSE_R) && !mouseRightClicked) {
		onMouseRightDown.Invoke();
		mouseRightClicked = true;
	}
	else if (!GetKey(KeyCode::MOUSE_R) && mouseRightClicked) {
		onMouseRightUp.Invoke();
		mouseRightClicked = false;
	}
}

bool InputManager::IsClicking()
{
	return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
}

bool InputManager::GetKey(KeyCode key)
{
	switch (key) {
	case KeyCode::MOUSE_L:
		return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
		break;

	case KeyCode::MOUSE_M:
		return (GetKeyState(VK_MBUTTON) & 0x8000) != 0;

		break;
	case KeyCode::MOUSE_R:
		return (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
		break;
	default:
		return false;
		break;
	}
}

