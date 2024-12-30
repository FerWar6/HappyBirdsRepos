#pragma once
#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include "Managers/GameManager.h"

class Object
{
public:
	Object();
	~Object();
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void Render(sf::RenderWindow& window) {};

	Component* GetComponent(std::string name);
	void AddComponent(Component* component);
	bool HasComponent(std::string compnentName);

protected:
	std::vector<Component*> components;
	GameManager* manager;
};