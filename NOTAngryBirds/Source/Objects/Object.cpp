#include "Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include <iostream>

Object::Object(bool setAsSelected)
	: manager(sl::GetGameManager()),
	transform()
{
	Start(setAsSelected);
}

Object::Object(Transform trans, bool setAsSelected)
	: manager(sl::GetGameManager()),
	transform(trans)
{
	Start(setAsSelected);
}

Object::Object(sf::Vector2f pos, float rot, sf::Vector2f size, bool setAsSelected)
	: manager(sl::GetGameManager()),
	transform(Vector2(pos.x, pos.y), rot, Size(size.x, size.y))
{
	Start(setAsSelected);
}

void Object::Start(bool setAsSel)
{
	if (setAsSel) sl::SetSelectedObj(this);
	manager->enginePtr->AddObject(this);
}

Object::~Object()
{
}

void Object::Update() {
	for (auto& comp : components) {
		comp->Update();
	}
}

void Object::FixedUpdate() {
	for (auto& comp : components) {
		comp->FixedUpdate();
	}
}

void Object::Render(sf::RenderWindow& w) {
	for (auto& comp : components) {
		comp->Render(w);
	}
}

Component* Object::GetComponent(ComponentType type)
{
	for (auto& comp : components) {
		if (comp->type == type) return comp;
	}
	std::cout << "returned nullptr from GetComponent\n";
	return nullptr;
}

Component* Object::GetComponent(int indexInVector)
{
	return components[indexInVector]->GetComponentPtr();
}

std::vector<Component*>& Object::GetComponents()
{
	return components;
}

void Object::AddComponent(Component* c)
{
	c->object = this;
	components.push_back(c);
}

bool Object::HasComponent(ComponentType type)
{
	for (auto& comp : components) {
		if (comp->type == type) return true;
	}
	return false;
}

const sf::Vector2f Object::GetPos()
{
	return sf::Vector2f(transform.position.x, transform.position.y);
}

const b2Vec2 Object::GetPosInM()
{
	int scale = manager->worldScale;
	return b2Vec2{ transform.position.x / scale, transform.position.y / scale};
}

void Object::SetPosInM(b2Vec2 posInM)
{
	int scale = manager->worldScale;
	transform.position.x = posInM.x * scale;
	transform.position.y = posInM.y * scale;
}

void Object::SetPos(sf::Vector2f pos)
{
	transform.position.x = pos.x;
	transform.position.y = pos.y;
}

void Object::SetPos(float x, float y)
{
	transform.position.x = x;
	transform.position.y = y;
}

const float Object::GetRot()
{
	return transform.rotation;
}

void Object::SetRot(float rot)
{
	transform.rotation = rot;
}

const sf::Vector2f Object::GetSize()
{
	return sf::Vector2f(transform.size.w, transform.size.h);
}

const b2Vec2 Object::GetSizeInM()
{
	int scale = manager->worldScale;
	//std::cout << transform.size.w / scale << "\n";
	return b2Vec2{ transform.size.w / scale, transform.size.h / scale };
}

void Object::SetSizeInM(b2Vec2 posInM)
{
	int scale = manager->worldScale;
	transform.size.w = posInM.x * scale;
	transform.size.h = posInM.y * scale;
}

void Object::SetSize(sf::Vector2f s)
{
	transform.size.w = s.x;
	transform.size.h = s.y;
}

const Transform Object::GetTransform()
{
	return transform;
}



