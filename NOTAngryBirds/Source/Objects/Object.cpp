#include "Object.h"
#include "Managers/ServiceLocator.h"

Object::Object(sf::FloatRect r)
	: manager(sl::GetGameManager()),
	rect(r)
{
	manager->AddObject(this);
}

Object::Object()
	: manager(sl::GetGameManager()), 
	rect(0,0,0,0) 
{
	manager->AddObject(this);
}

void Object::Update() {}
void Object::FixedUpdate() {}
void Object::Render(sf::RenderWindow& window) {}

sf::FloatRect Object::GetRect()
{
	return rect;
}

sf::Vector2f Object::GetPos()
{
	return rect.getPosition();
}

sf::Vector2f Object::GetSize()
{
	return rect.getSize();
}

void Object::Delete()
{
	manager->DeleteObject(this);
}
