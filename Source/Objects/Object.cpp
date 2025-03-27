#include "Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Engine/EngineCore.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Objects/Components/Components.h"
#include <iostream>
#include <sstream>

Object::Object()
	: transform()
{
	Start();
}

Object::Object(std::string data) // Construct object using string data
{
	Start();
	bool inEditMode = sl::GetEngine().inEditMode;
	std::istringstream stringData(data);
	
	stringData >> transform.position.x >> transform.position.y >> transform.rotation >> transform.size.w >> transform.size.h;
	int numOfComps;
	stringData >> numOfComps;

	for (int i = 0; i < numOfComps; i++) {
		int enumIndex;
		stringData >> enumIndex;
		ComponentType compType = (ComponentType)enumIndex;

		switch (compType) {
		case SPRITE_RENDERER:
		{
			std::string txrName;
			bool useOwnSize;
			bool lockRotation;
			sf::Vector2f origin;
			stringData >> txrName >> useOwnSize >> lockRotation >> origin.x >> origin.y;
			AddComponent<SpriteRenderer>(txrName, useOwnSize, lockRotation, origin);
			break;
		}
		case RECT_RIGIDBODY:
		{
			b2WorldId& id = sl::GetWorldId();
			float density;
			int bodyTypeIndex;
			b2BodyType bodyType;
			stringData >> density >> bodyTypeIndex;
			bodyType = (b2BodyType)bodyTypeIndex;
			RectRigidbody* body = AddComponent<RectRigidbody>(bodyType, density, id);
			if (inEditMode) body->active = false;
			break;
		}
		case CIRCLE_RIGIDBODY:
		{
			b2WorldId& id = sl::GetWorldId();
			float density;
			int bodyTypeIndex;
			b2BodyType bodyType;
			stringData >> density >> bodyTypeIndex;
			bodyType = (b2BodyType)bodyTypeIndex;
			CircleRigidbody* body = AddComponent<CircleRigidbody>(bodyType, density, id);
			if (inEditMode) body->active = false;
			break;
		}
		case BUTTON:
		{
			int funcIdIndex;
			ButtFuncId funcId;
			stringData >> funcIdIndex;
			funcId = (ButtFuncId)funcIdIndex;
			Button* button = AddComponent<Button>(funcId);
			if (inEditMode) button->active = false;
			break;
		}
		case DESTRUCTIBLE_ITEM:
		{
			float health;
			stringData >> health;
			AddComponent<DestructibleItem>(health);
			break;
		}
		case WINCONDITION_ITEM:
		{
			int score;
			stringData >> score;
			AddComponent<WinConditionItem>(score);
			break;
		}
		case LAUNCHER:
		{
			int ammo;
			stringData >> ammo;
			Launcher* launcher = AddComponent<Launcher>(2);
			if (inEditMode) launcher->active = false;
			break;
		}
		default:
			std::cout << "Invalid Component Type: " << compType << "\n";
			break;
		}
	}
	if (inEditMode) AddComponent<EditorItem>(); //adds editorItem if in edit mode
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
		sl::GetSceneEditor().AddObject(this);
	}
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

Component* Object::GetComponent(ComponentType type) // Get component using enum ComponentType
{
	for (auto& comp : components) {
		if (comp->type == type) return comp.get();
	}
	std::cout << "returned nullptr from GetComponent\n";
	return nullptr;
}

bool Object::GetComponent(Component*& ptr, ComponentType type)
{
	for (auto& comp : components) {
		if (comp.get()->type == type) 
		{
			ptr = comp.get();
			return true;
		}
	}
	ptr = nullptr;
	return false;
}

std::vector<std::unique_ptr<Component>>& Object::GetComponents()
{
	return components;
}

void Object::AddComponent(std::unique_ptr<Component> c) // Add component functionality with worse syntax
{
	components.push_back(std::move(c));
}

bool Object::HasComponent(ComponentType type) // returns true if object has the component
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
	int scale = sl::GetEngineCore().worldScale;
	return b2Vec2{ transform.position.x / scale, transform.position.y / scale};
}

void Object::SetPosInM(b2Vec2 posInM)
{
	int scale = sl::GetEngineCore().worldScale;
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
	int scale = sl::GetEngineCore().worldScale;
	//std::cout << transform.size.w / scale << "\n";
	return b2Vec2{ transform.size.w / scale, transform.size.h / scale };
}

void Object::SetSizeInM(b2Vec2 posInM)
{
	int scale = sl::GetEngineCore().worldScale;
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

void Object::Delete() // adds its own Object* to markedForDeletion
{
	Engine& eng = sl::GetEngine();
	if (!eng.inEditMode) {
		eng.DeleteObject(this);
	}
	else {
		sl::GetSceneEditor().DeleteObject(this);
	}
}

std::string Object::GetSaveData() // saves the transform, number of components and component data
{
	std::string data;
	Transform& t = transform;
	data += std::to_string(t.position.x) + " ";
	data += std::to_string(t.position.y) + " ";
	data += std::to_string(t.rotation) + " ";
	data += std::to_string(t.size.w) + " ";
	data += std::to_string(t.size.h) + " ";

	int numOfComps = components.size();
	if (HasComponent(EDITOR_ITEM)) numOfComps--; // if in editer mode the editor item component needs to be removed
	data += std::to_string(numOfComps) + " ";

	for (auto& com : components) {
		data += com->GetSaveData();
	}
	return data;
}



