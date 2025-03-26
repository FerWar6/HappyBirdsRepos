#pragma once
#include "Components/Component.h"
#include "DataTypes/Transform.h"
#include <box2d/box2d.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
class Object
{
public:
	Object();
	Object(std::string data);
	Object(Transform trans);
	Object(sf::Vector2f pos, float rotation = 0, sf::Vector2f size = sf::Vector2f(1, 1));
	void Update();
	void FixedUpdate();
	void Render(sf::RenderWindow& window);

	Component* GetComponent(ComponentType type); // Get component using enum ComponentType
	bool GetComponent(Component*& ptr, ComponentType type);
	std::vector<std::unique_ptr<Component>>& GetComponents();

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args); // Add component functionailty
	void AddComponent(std::unique_ptr<Component> component); // Add component functionality with worse syntax
	bool HasComponent(ComponentType type); // returns true if object has the component

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
	void Delete(); // adds its own Object* to markedForDeletion
	std::string GetSaveData(); // returns own transform plus all component data
private:
	void Start();
	Transform transform;
	std::vector<std::unique_ptr<Component>> components;
};

template<typename T, typename ...Args>
T* Object::AddComponent(Args && ...args) // Add component functionality using template
{
	static_assert(std::is_base_of_v<Component, T>, "T must derive from Component"); // try casting T as a component to check if T derives from base abstract class Component
	auto component = std::make_unique<T>(std::forward<Args>(args)...); // Make unique pointer for the T using arguments
	T* rawPtr = component.get(); // Gets raw ptr from component
	components.push_back(std::move(component)); // adds unique ptr to components by moving it into the vector
	return rawPtr; // return ptr (raw ptr, not unique ptr)
}