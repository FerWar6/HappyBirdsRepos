#pragma once
#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include "DataTypes/Transform.h"
#include "Managers/GameManager.h"

class Object
{
public:
	Object(bool setAsSelected = true);
	Object(sf::Vector2f pos, float rotation, sf::Vector2f size, bool setAsSelected = true);
	~Object();

	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(sf::RenderWindow& window);


	Component* GetComponent(std::string name);
	void AddComponent(Component* component);
	bool HasComponent(std::string compnentName);

	GameManager* manager;

	const sf::Vector2f GetPos() ;
	void SetPosInM(b2Vec2 posInM);
	void SetPos(sf::Vector2f pos);

	const float GetRot();
	void SetRot(float rot);

	const sf::Vector2f GetSize();
	void SetSizeInM(b2Vec2 sizeInM);
	void SetSize(sf::Vector2f size);

private:
	Transform transform;
	std::vector<Component*> components;
};