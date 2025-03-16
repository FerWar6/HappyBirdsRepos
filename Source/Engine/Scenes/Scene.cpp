#include "Scene.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/Button.h"
#include "Objects/Components//EditorItem.h"
#include <iostream>
#include <filesystem>
#include <fstream>
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
	std::cout << "Saved Scene! ( " << sceneName << " )\n";
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
				case ComponentType::SPRITE_RENDERER:
				{
					std::string txrName;
					file >> txrName;
					new SpriteRenderer(txrName);
					break;
				}
				case ComponentType::RECT_RIGIDBODY:
				{
					b2WorldId& id = sl::GetWorldId();
					float density;
					int bodyTypeIndex;
					b2BodyType bodyType;
					file >> density;
					file >> bodyTypeIndex;
					bodyType = (b2BodyType)bodyTypeIndex;
					new RectRigidbody(bodyType, density, id);
					break;
				}
				case ComponentType::CIRCLE_RIGIDBODY:
				{
					b2WorldId& id = sl::GetWorldId();
					float density;
					int bodyTypeIndex;
					b2BodyType bodyType;
					file >> density;
					file >> bodyTypeIndex;
					bodyType = (b2BodyType)bodyTypeIndex;
					new CircleRigidbody(bodyType, density, id);
					break;
				}
				case ComponentType::BUTTON:
				{
					int funcIdIndex;
					ButtFuncId funcId;
					file >> funcIdIndex;
					funcId = (ButtFuncId)funcIdIndex;
					new Button(funcId);
					break;
				}
				default:
					std::cout << "Invalid Component Type: " << compType << "\n";
					break;
				}
			}
			if (sl::GetEngine().inEditMode) new EditorItem(); //adds editorItem if in edit mode
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