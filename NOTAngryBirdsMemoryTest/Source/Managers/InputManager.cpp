#include "InputManager.h"
#include <windows.h>
#include <iostream>

InputManager::InputManager()
	: clicked(false)
{
}

void InputManager::InputCheck()
{

	if (IsClicking() && !clicked) {
		levelManager->AddObject(b2Vec2{ 5,-5 }, b2_dynamicBody);
		//do click thing
		std::cout << "Click action" << "\n";
		clicked = true;
	}
	else if (!IsClicking() && clicked) {
		//look to see if button up
		clicked = false;
	}
}

bool InputManager::IsClicking()
{
	return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
}

