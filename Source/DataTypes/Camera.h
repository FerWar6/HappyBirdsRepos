#pragma once
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Objects/Object.h";
#include <iostream>
class Camera {
public:
	Camera();
	void MoveToTarget();
	void SetView(sf::RenderWindow& win);
	sf::View& GetView();

	sf::Vector2f& GetPos();
	void SetPos(sf::Vector2f pos);
	void SetPos(float x, float y);

	sf::Vector2f& GetTargetPos();
	void SetTargetPos(sf::Vector2f targetPos);

	void SetCamSpeed(float speed);

	void SetFollowObject(Object* obj);
private:
	sf::View view;
	sf::Vector2f position;
	Object* followObject;
	sf::Vector2f targetPosition;
	float speed = 0.0015f;
	float lerp(float a, float b, float t);
};