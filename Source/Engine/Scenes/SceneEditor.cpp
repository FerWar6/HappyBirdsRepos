#include "SceneEditor.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Object.h"
#include "Managers/InputManager.h"
#include "Objects/Components/Component.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/EditorItem.h"
#include "UI/Hierarchy.h"
#include "UI/EditorMoveTool.h"
#include "Engine/PreLoader.h"
#include <filesystem>

namespace fs = std::filesystem;

SceneEditor::SceneEditor()
	: currentScene(nullptr),
	inputMan(sl::GetInputManager()),
	cam(),
	selObj(nullptr)
{
	sl::SetSceneEditor(this);

	new Hierarchy();
	new EditorMoveTool();
	inputMan.SetWindow(window);

	sf::Texture& txrRef = sl::GetPreLoader().GetTexture("EditorMove");
	moveWidgetSprite.setTexture(txrRef);
	moveWidgetSprite.setOrigin(sf::Vector2f(8, 92));
	std::cout << "\n";
	OpenEditorConsole();
}


void SceneEditor::OpenEditorConsole()
{
	LoadScenes();
	DebugScenes();

	bool loadFirstLevel = true;
	if (loadFirstLevel) {
		currentScene = &allScenes[0];
		OpenEditorWindow();
	}
	else {
		while (input != "exit") {
			std::cin >> input;
			CheckInput();
		}
	}
}

void SceneEditor::OpenEditorWindow()
{
	int winWidth = 1500;
	int winHeight = 900;
	std::string name = currentScene->sceneName;
	window.create(sf::VideoMode(winWidth, winHeight), name);
	cam.SetView(window);
	currentScene->LoadScene();

	sf::Texture& gridTxr = sl::GetPreLoader().GetTexture("GridSquare");
	gridTxr.setRepeated(true);
	sf::Vector2u winSize = window.getSize();
	gridSprite.setTexture(gridTxr);
	sf::IntRect rect(0, 0, winSize.x, winSize.y);
	gridSprite.setTextureRect(rect);

	LoopEditor();
}

void SceneEditor::LoopEditor()
{
	while (window.isOpen() && !inputMan.GetKey(ESCAPE))
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closed editor" << std::endl;
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
		inputMan.buttonManager.UpdateButtonCalls();
		//renderer functionality
		Render();
	}
	//shut down level editor
	currentScene->SaveScene();

}

void SceneEditor::Update()
{
	for (auto& obj : objects) {
		obj->Update();
	}
	for (auto& ui : uiElements) {
		ui->Update();
	}
}

void SceneEditor::Render()
{
	window.clear();
	window.setView(cam.GetView());

	window.draw(gridSprite);
	for (auto& obj : objects) {
		obj->Render(window);
	}
	for (auto& ui : uiElements) {
		ui->Render(window);
	}
	if (selObj) { 
		moveWidgetSprite.setPosition(selObj->GetPos());
		window.draw(moveWidgetSprite);
	}

	window.display();
}

void SceneEditor::UpdateInput()
{
	inputMan.UpdateMousePos();
	inputMan.UpdateInputs();

	if (inputMan.GetKey(MOUSE_R)) {
		window.setTitle(currentScene->sceneName + "*");
		sf::Vector2f newCamPos = (sf::Vector2f)(inputMan.GetOldMousePos() - inputMan.GetMousePos());
		cam.SetPos(cam.GetPos() + newCamPos);
	}
	else {
		//std::cout << "cam pos:  x: " << cam.GetPos().x << " y: " << cam.GetPos().y << "\n";
		//std::cout << "current mouse pos:  x: " << inputMan.GetMousePos().x << " y: " << inputMan.GetMousePos().y << "\n";
		//std::cout << "old mouse pos:  x: " << inputMan.GetOldMousePos().x << " y: " << inputMan.GetOldMousePos().y << "\n\n";
		inputMan.UpdateOldMousePos();
	}
	if (inputMan.GetKey(CONTROL) && inputMan.GetKeyDown(S)) {
		//TODO - actually save the game
		window.setTitle(currentScene->sceneName);
	}
	if (inputMan.GetKeyDown(MOUSE_L)) {

		for (auto& obj : objects) {
			if (((EditorItem*)obj->GetComponent(EDITOR_ITEM))->HoveringOver()) {
				((EditorItem*)obj->GetComponent(EDITOR_ITEM))->Select();
			}
		}
	}
}


void SceneEditor::CheckInput()
{
	//make the input lower case
	for (char& c : input) {
		c = std::tolower(static_cast<unsigned char>(c));
	}
	//check if input is name or index of level
	for (int i = 0; i < allScenes.size(); i++) {
		Scene& scene = allScenes[i];
		if (input == std::to_string(i) || input == scene.sceneName) {
			currentScene = &scene;
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
		DebugScenes();
		return;
	}
	if (input == "exit"){
		std::cout << "Exited level editor\n";
		return;
	}
	std::cout << "'" << input << "' Is not a valid command \n";
}
void SceneEditor::AddObject(Object* o)
{
	markedForAddition.push_back(o);
}
void SceneEditor::DeleteObject(Object* o)
{
	markedForDeletion.push_back(o);
}
void SceneEditor::AddUI(UIElement* ui)
{
	uiElements.push_back(ui);
}
void SceneEditor::UpdateObjectsVector()
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
void SceneEditor::SetSelectedObj(Object* obj)
{
	if (selObj) {
		((EditorItem*)selObj->GetComponent(EDITOR_ITEM))->SetSelected(false);
	}
	selObj = obj; //sets new selected object
	((EditorItem*)selObj->GetComponent(EDITOR_ITEM))->SetSelected(true);
}

Object* SceneEditor::GetSelectedObj()
{
	return selObj;
}

void SceneEditor::ClearSelectedObj()
{
	if (selObj) {
		((EditorItem*)selObj->GetComponent(EDITOR_ITEM))->SetSelected(false);
	}
	selObj = nullptr;
}

Camera& SceneEditor::GetCamera()
{
	return cam;
}

void SceneEditor::LoadScenes()
{
	for (const auto& entry : fs::directory_iterator(scenePath)) {
		std::string filepath = entry.path().string();

		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0))
		{
			allScenes.emplace_back(filepath);
			std::cout << "file found!: " << filepath << "\n";
		}
	}
}

void SceneEditor::DebugScenes()
{
	int numOfScenes = allScenes.size();
	if (numOfScenes == 0) {
		std::cout << "No levels found in: " << scenePath << "\n";
		return;
	}
	numOfScenes == 1 ? std::cout << numOfScenes << " Level found at: " << scenePath << "\n" : std::cout << numOfScenes << " Levels found at: " << scenePath << "\n";
	std::cout << "\n[-----------------------------------------------]\n";
	for (int i = 0; i < allScenes.size(); i++) {
		Scene& scene = allScenes[i];
		std::cout << "Level [" << i << "]  " << scene.sceneName << "\n";
	}
	std::cout << "[-----------------------------------------------]\n";
}