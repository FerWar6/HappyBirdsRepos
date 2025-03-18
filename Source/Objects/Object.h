#pragma once
#include "Components/Component.h"
#include "DataTypes/Transform.h"
#include "box2d/box2d.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
class Object
{
public:
	Object();
	Object(Transform trans);
	Object(sf::Vector2f pos, float rotation = 0, sf::Vector2f size = sf::Vector2f(1, 1));
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(sf::RenderWindow& window);

	Component* GetComponent(ComponentType type);
	bool GetComponent(Component*& ptr, ComponentType type);
	Component* GetComponent(int indexInVector);
	std::vector<std::unique_ptr<Component>>& GetComponents();

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args);
	void AddComponent(std::unique_ptr<Component> component);
	bool HasComponent(ComponentType type);

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

	std::string GetSaveData();
private:
	void Start();
	Transform transform;
	std::vector<std::unique_ptr<Component>> components;
};

template<typename T, typename ...Args>
inline T* Object::AddComponent(Args && ...args)
{
	static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
	auto component = std::make_unique<T>(std::forward<Args>(args)...);
	T* rawPtr = component.get();
	components.push_back(std::move(component));
	return rawPtr;
}