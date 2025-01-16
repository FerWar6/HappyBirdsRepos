#include "LevelManager.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
#include "Engine/Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/Button.h"
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;


LevelManager::LevelManager()
{
}

void LevelManager::LoadLevels()
{


	//for (const auto& entry : fs::directory_iterator(levelsPath)) {
	//	std::string filePath = entry.path().string();

	//	if (filePath.size() >= 4 && (filePath.compare(filePath.size() - 4, 4, ".txt") == 0))
	//	{

	//		std::cout << "file found!: " << filePath << "\n";
	//	}
	//}

	/*Object* obj = new Object();
	new RectRigidbody(b2Vec2{ 7, 3 }, b2Vec2{ 2, 2 }, b2_dynamicBody, 1, sl::GetGameManager()->GetWorldId());
	new SpriteRenderer("BoxPlaceholder");*/

	//std::string levelsPath = "Assets/Levels/level1.txt";
	std::string levelPath = "Assets/Levels/level1.txt";
	std::ofstream file;

	//file.open(levelsPath, std::ios::out); //write to text file
	//if (file.is_open()) {
	//	file << ObjToTxt(*obj) << "\n";
	//	file << ObjToTxt(*obj) << "\n";
	//	file.close();
	//}

	file.open(levelsPath, std::ios::app); //add to text file
	if (file.is_open()) {
		file.close();
	}

	LoadLevel(levelPath);
}

void LevelManager::SaveExistingLevel(std::string& lvlPath, std::vector<Object*> lvlObjs)
{
	std::ofstream file;
	file.open(lvlPath, std::ios::out); //write to text file
	if (file.is_open()) {
		for (auto obj : lvlObjs) {
			file << ObjToTxt(*obj) << "\n";
		}
		file.close();
	}
}

void LevelManager::SaveNewLevel(std::vector<Object*> lvlObjs)
{
	//create a new txt file and save the objects
	for (auto obj : lvlObjs) {

	}
}


std::string LevelManager::ObjToTxt(Object& obj)
{
	//saving an object saves its transform and its components
	//this is how the data is structured
	//	"obj" pos.x pos.y rot size.w size.h 
	//	"cps" compAmnt compType (all other component atributes)
	std::string str;
	Transform transform = obj.GetTransform();
	str += AddToSring(objId);
	str += AddToSring(transform.position.x);
	str += AddToSring(transform.position.y);
	str += AddToSring(transform.rotation);
	str += AddToSring(transform.size.w);
	str += AddToSring(transform.size.h);

	str += AddToSring(compsId);
	int numOfComps = obj.GetComponents().size();
	str += AddToSring(numOfComps);

	if (numOfComps > 0) for (int i = 0; i < numOfComps; i++) {
		//loop over each component in object and add them to the txt file
		Component* component = obj.GetComponent(i);
		ComponentType compType = component->type;

		str += AddToSring(compType);

		switch (compType) {
		case ComponentType::SPRITE_RENDERER: 
		{
			//saves name of texture
			SpriteRenderer* spriteRen = (SpriteRenderer*)component;
			str += AddToSring(spriteRen->txrName);
			break;
		}
		case ComponentType::RECT_RIGIDBODY:
		{
			//saves density and bodytype
			RectRigidbody* rectBody = (RectRigidbody*)component;
			str += AddToSring(rectBody->density);
			str += AddToSring(rectBody->GetBodyType());
			break;
		}
		case ComponentType::CIRCLE_RIGIDBODY:
		{
			//saves density and bodytype
			CircleRigidbody* cirlceBody = (CircleRigidbody*)component;
			str += AddToSring(cirlceBody->density);
			str += AddToSring(cirlceBody->GetBodyType());
			break;
		}		
		case ComponentType::BUTTON:
		{
			//TODO - save the onclick function of the button component
			//saves onclick function
			RectRigidbody* rectBody = (RectRigidbody*)component;
			break;
		}
		default:
			std::cout << "Invalid Component Type: " << compType << "\n";
			break;
		}
	}
	return str;
}

void LevelManager::LoadLevel(std::string& lvlPath)
{
	std::ifstream file; //this is a file pointer/cursor to somewhere in the file
	file.open(lvlPath, std::ios::in); //read from text file
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
			std::string dataType;
			file >> dataType; //checks if obj
			if (dataType == objId) {
				Transform transform;
				file >> transform.position.x;
				file >> transform.position.y;
				file >> transform.rotation;
				file >> transform.size.w;
				file >> transform.size.h;
				//create object from data
				Object* obj = new Object(transform);

				//add components
				file >> dataType; //checks if components
				int numOfComps;
				file >> numOfComps;

				if (numOfComps > 0) for (int i = 0; i < numOfComps; i++) {
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
						b2WorldId& id = sl::GetGameManager()->GetWorldId();
						float density;
						int enumIndex;
						b2BodyType bodyType;
						file >> density;
						file >> enumIndex;
						bodyType = (b2BodyType)enumIndex;
						new RectRigidbody(bodyType, density, id);
						break;
					}
					case ComponentType::CIRCLE_RIGIDBODY:
					{
						b2WorldId& id = sl::GetGameManager()->GetWorldId();
						float density;
						int enumIndex;
						b2BodyType bodyType;
						file >> density;
						file >> enumIndex;
						bodyType = (b2BodyType)enumIndex;
						new CircleRigidbody(bodyType, density, id);
						break;
					}
					case ComponentType::BUTTON:
					{
						//TODO - load the onclick button function from components
						std::function<void()> onButtonClick;
						new Button(onButtonClick);
						break;
					}
					default:
						std::cout << "Invalid Component Type: " << compType << "\n";
						break;
					}
				}
			}
		}
		file.close();
	}
	else {
		std::cout << "could find file: " << levelsPath << "\n";
	}
}

//TODO - use a template to make this into 1 function
std::string LevelManager::AddToSring(float num)
{
	return std::to_string(num) + " ";
}

std::string LevelManager::AddToSring(int num)
{
	return std::to_string(num) + " ";
}

std::string LevelManager::AddToSring(std::string string)
{
	return string + " ";
}
