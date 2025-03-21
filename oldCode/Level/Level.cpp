//#include "Level.h"
//#include <iostream>
//#include "Managers/ServiceLocator.h"
//#include "Engine/Engine.h"
//#include "Objects/Object.h"
//#include "Objects/Components/SpriteRenderer.h"
//#include "Objects/Components/RectRigidbody.h"
//#include "Objects/Components/CircleRigidbody.h"
//#include "Objects/Components/Button.h"
//#include "Objects/Components//EditorItem.h"
//#include <filesystem>
//#include <fstream>
//
//Level::Level(std::string& pathToLvl)
//	: pathToLevel(pathToLvl),
//	levelName(GetNameFromPath())
//{
//}
//
//void Level::SaveLevel()
//{
//
//}
//
//void Level::LoadLevel() //load level inside of game
//{
//	std::ifstream file; //this is a file pointer/cursor to somewhere in the file
//	file.open(pathToLevel, std::ios::in); //read from text file
//	if (file.is_open()) {
//		//count the amount of objects in file
//		std::string line;
//		int amountOfObj = 0;
//		while (std::getline(file, line)) {
//			amountOfObj++;
//		}
//		file.clear();
//		file.seekg(0, std::ios::beg);
//
//		for (int i = 0; i < amountOfObj; i++) {
//			std::string dataType;
//			file >> dataType; //checks if obj
//			if (dataType == "obj") {
//				Transform transform;
//				file >> transform.position.x;
//				file >> transform.position.y;
//				file >> transform.rotation;
//				file >> transform.size.w;
//				file >> transform.size.h;
//				//create object from data
//				new Object(transform);
//				//add components
//				file >> dataType; //checks if components
//				int numOfComps;
//				file >> numOfComps;
//
//				for (int i = 0; i < numOfComps; i++) {
//					//create component based on data in file
//					int enumIndex;
//					file >> enumIndex;
//					ComponentType compType = (ComponentType)enumIndex;
//
//					switch (compType) {
//					case ComponentType::SPRITE_RENDERER:
//					{
//						std::string txrName;
//						file >> txrName;
//						new SpriteRenderer(txrName);
//						break;
//					}
//					case ComponentType::RECT_RIGIDBODY:
//					{
//						b2WorldId& id = sl::GetWorldId();
//						float density;
//						int enumIndex;
//						b2BodyType bodyType;
//						file >> density;
//						file >> enumIndex;
//						bodyType = (b2BodyType)enumIndex;
//						new RectRigidbody(bodyType, density, id);
//						break;
//					}
//					case ComponentType::CIRCLE_RIGIDBODY:
//					{
//						b2WorldId& id = sl::GetWorldId();
//						float density;
//						int enumIndex;
//						b2BodyType bodyType;
//						file >> density;
//						file >> enumIndex;
//						bodyType = (b2BodyType)enumIndex;
//						new CircleRigidbody(bodyType, density, id);
//						break;
//					}
//					case ComponentType::BUTTON:
//					{
//						int funcIdIndex;
//						ButtFuncId funcId;
//						file >> funcIdIndex;
//						funcId = (ButtFuncId)funcIdIndex;
//						new Button(funcId);
//						break;
//					}
//					default:
//						std::cout << "Invalid Component Type: " << compType << "\n";
//						break;
//					}
//				}
//				if(sl::GetEngine().inEditMode) new EditorItem(); //adds editorItem if in edit mode
//			}
//			else {
//				std::cout << "Data in " << pathToLevel << " not an object. \n";
//			}
//		}
//		file.close();
//	}
//	else {
//		std::cout << "could find file: " << pathToLevel << "\n";
//	}
//}
//
//std::string Level::GetNameFromPath()
//{
//	std::string name = pathToLevel;
//
//	size_t charPos;
//	charPos = name.find_last_of("/");
//
//	if (charPos != std::string::npos) {
//		name.erase(name.begin(), name.begin() + charPos + 1); //plus one to include the slash itself
//	}
//
//	charPos = name.find_last_of(".");
//	if (charPos != std::string::npos) {
//		name.erase(name.begin() + charPos, name.end());
//	}
//
//	return name;
//}