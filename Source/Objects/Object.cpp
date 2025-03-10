#include "Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Level/LevelEditor.h"
#include <iostream>

Object::Object()
	: transform()
{
	Start();
}

Object::Object(Transform trans)
	: transform(trans)
{
	Start();
}

Object::Object(sf::Vector2f pos, float rot, sf::Vector2f size)
	: transform(Vector2(pos.x, pos.y), rot, Size(size.x, size.y))
{
	Start();
}

void Object::Start()
{
	sl::SetSelectedObj(this);
	Engine& eng = sl::GetEngine();
	if (!eng.inEditMode) {
		eng.AddObject(this);
	}
	else {
		sl::GetLevelEditor().AddObject(this);
	}
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

bool Object::GetComponent(Component* ptr, ComponentType type)
{
	for (auto* comp : components) {
		if (comp->type == type) ptr = comp;
	}
	return ptr;
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
	int scale = sl::GetEngine().worldScale;
	return b2Vec2{ transform.position.x / scale, transform.position.y / scale};
}

void Object::SetPosInM(b2Vec2 posInM)
{
	int scale = sl::GetEngine().worldScale;
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
	int scale = sl::GetEngine().worldScale;
	//std::cout << transform.size.w / scale << "\n";
	return b2Vec2{ transform.size.w / scale, transform.size.h / scale };
}

void Object::SetSizeInM(b2Vec2 posInM)
{
	int scale = sl::GetEngine().worldScale;
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

std::string Object::GetSaveData()
{
	std::string data;
	Transform& t = transform;
	data += "obj ";
	data += std::to_string(t.position.x) + " ";
	data += std::to_string(t.position.y) + " ";
	data += std::to_string(t.rotation) + " ";
	data += std::to_string(t.size.w) + " ";
	data += std::to_string(t.size.h) + " ";

	data += "cps ";
	int numOfComps = components.size();
	data += std::to_string(numOfComps) + " ";

	for (int i = 0; i < numOfComps; i++) {
		data += GetComponent(i)->GetSaveData();
	}
	return data;
}



