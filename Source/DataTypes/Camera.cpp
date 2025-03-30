#include "Camera.h"
#include "Managers/ServiceLocator.h"
#include "Engine/EngineCore.h"
#include <iostream>
Camera::Camera()
	:	followObject(nullptr)
{}

void Camera::MoveToTarget()
{
	if (followObject) {
		//std::cout << deltaTime << " deltatime\n";
		float xpos = lerp(position.x, followObject->GetPos().x - offset, speed);
		SetPos(xpos, position.y);
	}
	else {
		float newxpos = 0;
		float xpos = lerp(position.x, newxpos, speed);
		SetPos(xpos, position.y);
	}
	//std::cout << speed << " cam speed\n";

}


void Camera::SetView(sf::RenderWindow& win)
{
	view = win.getDefaultView();
}

sf::View& Camera::GetView()
{
	return view;
}

void Camera::SetPos(sf::Vector2f pos)
{
	sf::Vector2f newPos = pos - position;
	view.move(newPos);
	position = pos;
	//std::cout << "x: " << position.x << " y:" << position.y << "\n";
}

void Camera::SetPos(float x, float y)
{
	sf::Vector2f pos(x, y);
	sf::Vector2f newPos = pos - position;
	view.move(newPos);
	position = pos;

	//std::cout << "x: " << position.x << " y: " << position.y << "\n";
}

sf::Vector2f& Camera::GetPos()
{
	return position;
}

void Camera::SetCamSpeed(float s)
{
	speed = s;
}

bool Camera::ReachedTarget()
{
	float reachedThreshold = 0.1f;
	float targetPos;
	if (followObject) targetPos = followObject->GetPos().x - offset;
	else targetPos = 0;
	if (targetPos > position.x) {
		return targetPos < position.x + reachedThreshold;
	}
	else if (targetPos < position.x) {
		return targetPos > position.x - reachedThreshold;
	}
	return false;
}

void Camera::SetFollowObject(Object* obj)
{
	followObject = obj;
}

Object* Camera::GetFollowObject()
{
	return followObject;
}

float Camera::lerp(float a, float b, float t)
{
	float deltaTime = sl::GetEngineCore().GetDeltaTime();
	return a + (t * deltaTime) * (b - a);
}
