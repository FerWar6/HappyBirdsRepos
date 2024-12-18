#include "InputManager.h"
#include "Engine/Engine.h"
#include <windows.h>
#include <iostream>

InputManager::InputManager(Engine* e)
	: enginePtr(e),
	clicked(false)
{}

void InputManager::InputCheck()
{
	cursorPos = sf::Mouse::getPosition(enginePtr->GetManager()->GetWindow());
	//std::cout << "x: " << cursorPos.x << " y: " << cursorPos.y << "\n";
	if (IsClicking() && !clicked) {
		int scale = 50;
		//on click down action
		sf::Vector2i posVec = enginePtr->gameManager.gridPtr->posOnGrid;
		b2Vec2 spawnPos = b2Vec2{ ((float)posVec.x / scale) + .25f, ((float)posVec.y / scale) + .25f };
		//b2Vec2{ (float)posVec.x / scale, (float)posVec.y / scale }
		//b2Vec2 pos = b2Vec2{ pos.x / scale, pos.y / scale };
		//std::cout << "x: " << pos.x << " y: " << pos.y << "\n";
		enginePtr->GetGameObjects().push_back(std::make_unique<PhysicsObject>(spawnPos, b2Vec2{.5, .5}));

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

