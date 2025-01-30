#include "LevelEditor.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Object.h"
#include "Managers/GameManager.h"
#include "Managers/InputManager.h"
#include "Objects/Components/Component.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/EditorItem.h"
#include "Engine/PreLoader.h"
#include <filesystem>

namespace fs = std::filesystem;

LevelEditor::LevelEditor(InputManager& input, LevelEditor* selfPtr)
	: currentLevel(nullptr),
	inputMan(input),
	cam(),
	selObj(nullptr)
{
	sl::SetLevelEditor(this);
	inputMan.SetWindow(window);




	sf::Texture& txrRef = sl::GetPreLoader()->GetTexture("EditorMove");
	moveWidgetSprite.setTexture(txrRef);
	moveWidgetSprite.setOrigin(sf::Vector2f(8, 92));
	selfPtr = this;
	std::cout << "\n";
	OpenEditorConsole();
}


void LevelEditor::OpenEditorConsole()
{
	LoadLevels();
	DebugLevels();

	bool loadFirstLevel = true;
	if (loadFirstLevel) {
		currentLevel = &allLevels[0];
		OpenEditorWindow();
	}
	else {
		while (input != "exit") {
			std::cin >> input;
			CheckInput();
		}
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


	sf::Texture& gridTxr = sl::GetPreLoader()->GetTexture("GridSquare");
	gridTxr.setRepeated(true);
	sf::Vector2u winSize = window.getSize();
	gridSprite.setTexture(gridTxr);
	sf::IntRect rect(0, 0, winSize.x, winSize.y);
	gridSprite.setTextureRect(rect);


	LoopEditor();
}

void LevelEditor::LoopEditor()
{
	while (window.isOpen() && !inputMan.GetKey(ESCAPE))
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine" << std::endl;
				window.close();
			}
		}
		if (inputMan.GetKey(CONTROL) && inputMan.GetKey(C)) {
			std::cout << "pressed ctrl\n";
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
		Update();
		UpdateInput();
		//renderer functionality
		Render();
	}
}

void LevelEditor::Update()
{
	for (auto& obj : objects) {
		obj->Update();
	}
}

void LevelEditor::Render()
{
	window.clear();
	window.setView(cam.GetView());

	window.draw(gridSprite);
	for (auto& obj : objects) {
		obj->Render(window);
	}
	if (selObj) {
		moveWidgetSprite.setPosition(selObj->GetPos());
		window.draw(moveWidgetSprite);
	}

	window.display();
}

void LevelEditor::UpdateInput()
{
	inputMan.SetMousePos(window);
	inputMan.UpdateInputs();

	if (inputMan.GetKey(MOUSE_R)) {
		cam.SetPos(cam.GetPos() + (sf::Vector2f)(inputMan.oldMousePos - inputMan.mousePos));
	}
	else {
		inputMan.oldMousePos = inputMan.mousePos;
	}
	int increment = 50;
	if (inputMan.GetKeyDown(ARROW_UP) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.y -= increment;
		selObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDown(ARROW_DOWN) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.y += increment;
		selObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDown(ARROW_LEFT) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.x -= increment;
		selObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDown(ARROW_RIGHT) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.x += increment;
		selObj->SetPos(newPos);
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
void LevelEditor::SetSelectedObj(Object* obj)
{
	if (selObj) {
		((EditorItem*)selObj->GetComponent(EDITOR_ITEM))->SetSelected(false);
	}
	selObj = obj; //sets new selected object
	((EditorItem*)selObj->GetComponent(EDITOR_ITEM))->SetSelected(true);
}

void LevelEditor::ClearSelectedObj()
{
	if (selObj) {
		((EditorItem*)selObj->GetComponent(EDITOR_ITEM))->SetSelected(false);
	}
	selObj = nullptr;
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