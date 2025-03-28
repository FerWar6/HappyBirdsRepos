#include "Camera.h"
#include "Managers/ServiceLocator.h"
#include "Engine/EngineCore.h"
#include <iostream>
Camera::Camera()
	:	followObject(nullptr)
{}

void Camera::MoveToTarget()
{
	float deltaTime = sl::GetEngineCore().GetDeltaTime();
	if (followObject) {
		sf::Vector2f newPos = sf::Vector2f(followObject->GetPos().x - 750, followObject->GetPos().y - 400);
		//std::cout << deltaTime << " deltatime\n";
		float xpos = lerp(position.x, newPos.x, speed * deltaTime);
		float ypos = lerp(position.y, newPos.y, speed * deltaTime);
		SetPos(xpos, position.y);
	}
	else {
		float newxpos = 0;
		float xpos = lerp(position.x, newxpos, speed * deltaTime);
		SetPos(xpos, position.y);
	}
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

sf::Vector2f& Camera::GetTargetPos()
{
	return targetPosition;
}

void Camera::SetTargetPos(sf::Vector2f targetPos)
{
	targetPosition = targetPos;
}

void Camera::SetCamSpeed(float s)
{
	speed = s;
}

void Camera::SetFollowObject(Object* obj)
{
	followObject = obj;
}

float Camera::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
