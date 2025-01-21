#include "InputManager.h"
#include "Engine/Engine.h"
#include "Managers/ServiceLocator.h"
#include "Managers/GameManager.h"
#include <windows.h>
#include <iostream>

InputManager::InputManager()
	: mouseLeftClicked(false),
	mouseRightClicked(false)
{}

void InputManager::UpdateInputs()
{
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

void InputManager::SetMousePos(sf::RenderWindow& win)
{
	mousePos = sf::Mouse::getPosition(win);
}

bool InputManager::GetKeyDown(KeyCode key)
{
	return false;
}

bool InputManager::GetKeyUp(KeyCode key)
{
	return false;
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

void InputManager::InstantiateInputKeys()
{
	for (int i = 0; i < KeyCode::COUNT; i++) {

	}
}

