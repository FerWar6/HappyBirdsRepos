#include "InputManager.h"
#include "Engine/Engine.h"
#include "Level/Launcher.h"
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
		//sf::Vector2i posVec = enginePtr->GetManager()->gridPtr->posOnGrid;
		//b2Vec2 spawnPos = b2Vec2{ ((float)posVec.x / scale) + .25f, ((float)posVec.y / scale) + .25f };
		b2Vec2 spawnPos = b2Vec2{ enginePtr->launcherRef->GetLaunchPoint().x / scale,enginePtr->launcherRef->GetLaunchPoint().y / scale };
		//std::cout << "x: " << enginePtr->launcherRef->GetLaunchMomentum().x << " y: " << enginePtr->launcherRef->GetLaunchMomentum().y << "\n";
		PhysicsObject* obj = new PhysicsObject(spawnPos, b2Vec2{ .5, .5 }, enginePtr->launcherRef->GetLaunchMomentum());

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

