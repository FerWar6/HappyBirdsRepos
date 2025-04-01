#pragma once
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Objects/Object.h";
#include <iostream>
class Camera {
public:
	Camera();
	void MoveToTarget(); // moves to target if target is not a nullptr
	void SetView(sf::RenderWindow& win);
	sf::View& GetView();

	sf::Vector2f& GetPos();
	void SetPos(sf::Vector2f pos);
	void SetPos(float x, float y);

	void SetCamSpeed(float speed);
	bool ReachedTarget(); // returns true if the targetpos and currentpos are the same +- the threshold
	void SetFollowObject(Object* obj);
	Object* GetFollowObject();
private:
	float offset = 750 - 200; //sets the camera more to the right
	sf::View view;
	sf::Vector2f position;
	Object* followObject;
	float speed = 3; // speed of the camera
	float lerp(float a, float b, float t); //basic lerp function
};