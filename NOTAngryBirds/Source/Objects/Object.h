#pragma once
#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include "DataTypes/Transform.h"
#include "Managers/GameManager.h"

class Object
{
public:
	Object(bool setAsSelected = true);
	Object(Transform trans, bool setAsSelected = true);
	Object(sf::Vector2f pos, sf::Vector2f size = sf::Vector2f(0,0), float rotation = 0, bool setAsSelected = true);
	~Object();

	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(sf::RenderWindow& window);


	Component* GetComponent(ComponentType type);
	Component* GetComponent(int indexInVector);
	std::vector<Component*>& GetComponents();
	void AddComponent(Component* component);
	bool HasComponent(ComponentType type);

	GameManager* manager;

	const sf::Vector2f GetPos();
	const b2Vec2 GetPosInM();
	void SetPosInM(b2Vec2 posInM);
	void SetPos(sf::Vector2f pos);
	void SetPos(float x, float y);

	const float GetRot();
	void SetRot(float rot);

	const sf::Vector2f GetSize();
	const b2Vec2 GetSizeInM();
	void SetSizeInM(b2Vec2 sizeInM);
	void SetSize(sf::Vector2f size);

	const Transform GetTransform();
private:
	void Start(bool setAsSelected);
	Transform transform;
	std::vector<Component*> components;
};