#include "Scene.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <box2d/box2d.h>

Scene::Scene(std::string& pathToScne)
	: pathToScene(pathToScne),
	sceneName(GetNameFromPath())
{
}

void Scene::SaveScene(std::vector<Object*>& objects)
{
	std::ofstream file;
	file.open(pathToScene, std::ios::out); //write to text file
	if (file.is_open()) {
		for (auto obj : objects) {
			file << obj->GetSaveData() << "\n";
		}
		file.close();
	}
	std::cout << "Scene saved: " << sceneName << "\n";
}

void Scene::LoadScene()
{
	//TODO - read the file and load all of the objects inside of the file
	std::ifstream file; //this is a file pointer/cursor to somewhere in the file
	file.open(pathToScene, std::ios::in); //read from text file
	if (file.is_open()) {
		//count the amount of objects in file
		std::string line;
		int amountOfObj = 0;
		while (std::getline(file, line)) {
			amountOfObj++;
		}
		file.clear();
		file.seekg(0, std::ios::beg);

		for (int i = 0; i < amountOfObj; i++) {

			Transform transform;
			file >> transform.position.x;
			file >> transform.position.y;
			file >> transform.rotation;
			file >> transform.size.w;
			file >> transform.size.h;
			//create object from data
			Object* obj = new Object(transform);

			//add components
			int numOfComps;
			file >> numOfComps;

			for (int i = 0; i < numOfComps; i++) {
				//create component based on data in file
				int enumIndex;
				file >> enumIndex;
				ComponentType compType = (ComponentType)enumIndex;

				switch (compType) {
				case SPRITE_RENDERER:
				{
					std::string txrName;
					bool useOwnSize;
					bool lockRotation;
					sf::Vector2f origin;
					file >> txrName;
					file >> useOwnSize;
					file >> lockRotation;
					file >> origin.x;
					file >> origin.y;
					obj->AddComponent<SpriteRenderer>(txrName, useOwnSize, lockRotation, origin);
					break;
				}
				case RECT_RIGIDBODY:
				{
					b2WorldId& id = sl::GetWorldId();
					float density;
					int bodyTypeIndex;
					b2BodyType bodyType;
					file >> density;
					file >> bodyTypeIndex;
					bodyType = (b2BodyType)bodyTypeIndex;
					obj->AddComponent<RectRigidbody>(bodyType, density, id);
					break;
				}
				case CIRCLE_RIGIDBODY:
				{
					b2WorldId& id = sl::GetWorldId();
					float density;
					int bodyTypeIndex;
					b2BodyType bodyType;
					file >> density;
					file >> bodyTypeIndex;
					bodyType = (b2BodyType)bodyTypeIndex;
					obj->AddComponent<CircleRigidbody>(bodyType, density, id);
					break;
				}
				case BUTTON:
				{
					int funcIdIndex;
					ButtFuncId funcId;
					file >> funcIdIndex;
					funcId = (ButtFuncId)funcIdIndex;
					obj->AddComponent<Button>(funcId);
					break;
				}
				case DESTRUCTIBLE_ITEM:
				{
					float health;
					file >> health;
					obj->AddComponent<DestructibleItem>(health);
					break;
				}
				case WINCONDITION_ITEM:
				{
					int score;
					file >> score;
					obj->AddComponent<WinConditionItem>(score);
					break;
				}
				case LAUNCHER:
				{
					int ammo;
					file >> ammo;
					obj->AddComponent<Launcher>(2);
					break;
				}
				default:
					std::cout << "Invalid Component Type: " << compType << "\n";
					break;
				}
			}
			if (sl::GetEngine().inEditMode) obj->AddComponent<EditorItem>(); //adds editorItem if in edit mode
		}
		file.close();
	}
	else {
		std::cout << "could find file: " << pathToScene << "\n";
	}
}

std::string Scene::GetNameFromPath()
{
	std::string name = pathToScene;

	size_t charPos;
	charPos = name.find_last_of("/");

	if (charPos != std::string::npos) {
		name.erase(name.begin(), name.begin() + charPos + 1); //plus one to include the slash itself
	}
	
	charPos = name.find_last_of(".");
	if (charPos != std::string::npos) {
		name.erase(name.begin() + charPos, name.end());
	}

	return name;
}