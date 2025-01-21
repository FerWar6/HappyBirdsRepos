#include "LevelEditor.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
#include "Managers/GameManager.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
#include <filesystem>
#include <cctype>

namespace fs = std::filesystem;

LevelEditor::LevelEditor(InputManager& input, LevelEditor* selfPtr)
	: currentLevel(nullptr),
	inputMan(input),
	cam()
{
	sf::Texture& txrRef = sl::GetPreLoader()->GetTexture("EditorMove");
	moveWidgetSprite.setTexture(txrRef);
	selfPtr = this;
	std::cout << "\n";
	OpenEditorConsole();
}


void LevelEditor::OpenEditorConsole()
{
	LoadLevels();
	DebugLevels();
	while (input != "exit") {
		std::cin >> input;
		CheckInput();
	}
}

void LevelEditor::OpenEditorWindow()
{
	int winWidth = 1500;
	int winHeight = 900;
	std::string name = currentLevel->levelName;
	window.create(sf::VideoMode(winWidth, winHeight), name);
	cam.SetView(window);
	currentLevel->LoadLevel(markedForAddition);
	LoopEditor();
}

void LevelEditor::LoopEditor()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine" << std::endl;
				window.close();
			}
		}
		UpdateObjectsVector();

		sf::Time elapsed = gameClock.restart();
		accumulator += elapsed.asSeconds();

		//TO-DO: check for any updates in gameobjects
		while (accumulator >= timeStep) {
			//engine fixedupdate functionality
			for (auto& obj : objects) {
				//obj->FixedUpdate();
			}
			accumulator -= timeStep;
		}
		//engine update functionality
		inputMan.SetMousePos(window);
		inputMan.UpdateInputs();
		for (auto& obj : objects) {
			//obj->Update();
		}

		//renderer functionality
		window.setView(cam.GetView());
		window.clear();
		for (auto& obj : objects) {
			obj->Render(window);
		}
		moveWidgetSprite.setPosition((sf::Vector2f)inputMan.mousePos);
		window.draw(moveWidgetSprite);
		window.display();
		if (inputMan.GetKey(KeyCode::MOUSE_L)) {
			cam.SetPos((sf::Vector2f)(testOldMousePos - inputMan.mousePos));
			//move view based on the viewpos before this was called and the
		}
		else
		{
			testOldMousePos = inputMan.mousePos + (sf::Vector2i)cam.GetPos();
		}
		if (inputMan.GetKey(KeyCode::MOUSE_R)) {
			cam.SetPos(0,0);
		}
	}
}
void LevelEditor::CheckInput()
{
	//make the input lower case
	for (char& c : input) {
		c = std::tolower(static_cast<unsigned char>(c));
	}
	//check if input is name or index of level
	for (int i = 0; i < allLevels.size(); i++) {
		Level& level = allLevels[i];
		if (input == std::to_string(i) || input == level.levelName) {
			currentLevel = &level;
			OpenEditorWindow();
			return;
		}
	}
	if (input == "help") {
		std::cout << "'[i]' Index of level to open level\n";
		std::cout << "'name' Name of level to open level\n";
		std::cout << "'levels' Debug all levels found\n";
		std::cout << "'exit' Exit the editor\n";
		return;
	}
	if (input == "levels") {
		DebugLevels();
		return;
	}
	if (input == "exit"){
		std::cout << "Exited level editor\n";
		return;
	}
	std::cout << "'" << input << "' Is not a valid command \n";
}
void LevelEditor::UpdateObjectsVector()
{
	if (!markedForAddition.empty()) {
		objects.insert(objects.end(), markedForAddition.begin(), markedForAddition.end());
		markedForAddition.clear();
	}

	if (!markedForDeletion.empty()) {
		for (Object* obj : markedForDeletion) {
			auto it = std::find(objects.begin(), objects.end(), obj);
			if (it != objects.end()) {
				objects.erase(it);
			}
			delete obj;
			obj = nullptr;
		}
		markedForDeletion.clear();
	}
}
void LevelEditor::SetSelectedObject()
{
	std::cout << "test" << std::endl;

}

void LevelEditor::LoadLevels()
{
	for (const auto& entry : fs::directory_iterator(levelPath)) {
		std::string filepath = entry.path().string();

		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0))
		{
			Level level(filepath);
			allLevels.push_back(level);
		}
	}
}

void LevelEditor::DebugLevels()
{
	int numOfLev = allLevels.size();
	if (numOfLev == 0) {
		std::cout << "No levels found in: " << levelPath << "\n";
		return;
	}
	numOfLev == 1 ? std::cout << numOfLev << " Level found at: " << levelPath << "\n" : std::cout << numOfLev << " Levels found at: " << levelPath << "\n";
	std::cout << "\n[-----------------------------------------------]\n";
	for (int i = 0; i < allLevels.size(); i++) {
		Level& level = allLevels[i];
		std::cout << "Level [" << i << "]  " << level.levelName << "\n";
	}
	std::cout << "[-----------------------------------------------]\n";
}