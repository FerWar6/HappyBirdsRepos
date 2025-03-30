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

	void SetCamSpeed(float speed);
	bool ReachedTarget();
	void SetFollowObject(Object* obj);
	Object* GetFollowObject();
private:
	float offset = 750 - 200; //sets the camera more to the right
	sf::View view;
	sf::Vector2f position;
	Object* followObject;
	float speed = 3;
	float lerp(float a, float b, float t);
};