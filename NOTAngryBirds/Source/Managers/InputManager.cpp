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
	//mouseOne, mouseOneDown, mouseOneUp
	cursorPos = sf::Mouse::getPosition(enginePtr->GetManager()->GetWindow());
	//std::cout << "x: " << cursorPos.x << " y: " << cursorPos.y << "\n";
	if (IsClicking() && !clicked) {
		int scale = 50;
		//on click down action

		b2Vec2 spawnPos = b2Vec2{ enginePtr->launcherPtr->GetLaunchPoint().x / scale,enginePtr->launcherPtr->GetLaunchPoint().y / scale };

		Object* obj = new Object();

		//add starting velocity
		float ballSize = 0.5f;
		CircleRigidbody* body = new CircleRigidbody(spawnPos, ballSize, enginePtr->launcherPtr->GetLaunchMomentum(), enginePtr->GetManager()->GetWorldId());
		obj->AddComponent(body);

		SpriteRenderer* ren = new SpriteRenderer("CannonBall");
		obj->AddComponent(ren);

		//std::cout << "Click action" << "\n";
		onMouseLeftDown.Invoke();
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

bool InputManager::GetKey(KeyCode key)
{
	switch (key) {
	case KeyCode::MouseLeft:
		return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
		break;

	case KeyCode::MouseMiddle:
		return (GetKeyState(VK_MBUTTON) & 0x8000) != 0;

		break;
	case KeyCode::MouseRight:

		break;
	default:
		return false;
		break;
	}
}

