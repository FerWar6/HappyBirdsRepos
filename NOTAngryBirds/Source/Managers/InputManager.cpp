#include "InputManager.h"
#include "Engine/Engine.h"
#include "Level/Launcher.h"

#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"


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

		b2Vec2 spawnPos = b2Vec2{ enginePtr->launcherPtr->GetLaunchPoint().x / scale,enginePtr->launcherPtr->GetLaunchPoint().y / scale };

		Object* obj = new Object();

		//add starting velocity
		float ballSize = 0.5f;
		CircleRigidbody* body = new CircleRigidbody(*obj, spawnPos, ballSize, enginePtr->launcherPtr->GetLaunchMomentum(), enginePtr->GetManager()->GetWorldId());
		obj->AddComponent(body);

		sf::Texture& txr = enginePtr->GetPreLoader().GetTexture("CannonBall");
		SpriteRenderer* ren = new SpriteRenderer(*obj, txr);
		obj->AddComponent(ren);

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

