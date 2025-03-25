#include "SceneEditor.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
#include <filesystem>

namespace fs = std::filesystem;

SceneEditor::SceneEditor(Scene& scene)
	: editorScene(&scene),
	inputMan(sl::GetInputManager()),
	cam(),
	hierarchy(objects),
	moveTool(selectedObj),
	selectedObj(nullptr)
{
	std::cout << "Opened editor \n";
	std::cout << "Editing scene: " << scene.sceneName << "\n";
	sl::SetSceneEditor(this); // set as nullptr when exiting?
	inputMan.SetWindow(window);

	OpenEditorWindow();
}

SceneEditor::~SceneEditor()
{
	editorScene->SaveScene(objects);
	for (auto& obj : objects) {
		delete obj;
		obj = nullptr;
	}
	std::cout << "Closed editor \n";
}


void SceneEditor::OpenEditorWindow()
{
	int winWidth = 1500;
	int winHeight = 900;
	std::string& name = editorScene->sceneName;
	window.create(sf::VideoMode(winWidth, winHeight), name);
	cam.SetView(window);
	editorScene->LoadScene(); // Load the current scene into the editor

	// TODO - intergrate this into a grid component
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
			inputMan.HandleEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (inputMan.GetKey(CONTROL) && inputMan.GetKey(C)) { // shortcut test
			std::cout << "pressed ctrl\n";
		}
		UpdateObjectsVector();

		sf::Time elapsed = gameClock.restart();
		accumulator += elapsed.asSeconds();

		while (accumulator >= timeStep) {
			//engine fixedupdate functionality
			for (auto& obj : objects) {
				//obj->FixedUpdate();
			}
			accumulator -= timeStep;
		}
		//engine update functionality
		Update();
		//renderer functionality
		Render();
	}
	//shut down level editor
}

void SceneEditor::Update()
{
	inputMan.UpdateMousePos();
	inputMan.UpdateInputs();

	//hierarchy.Update(); //temp turned off bc its incomplete and in the way
	moveTool.Update();
	for (auto& obj : objects) {
		obj->Update();
	}
	if(inputMan.GetScrollWheel(SCROLL_UP)) { // Change camera zoom
		cam.IncreaseZoom();
	}
	if (inputMan.GetScrollWheel(SCROLL_DOWN)) {
		cam.DecreaseZoom();
	}
	if (inputMan.GetKey(MOUSE_R)) { // Adds camera grab functionality 
		window.setTitle(editorScene->sceneName + "*");
		sf::Vector2f newCamPos = (sf::Vector2f)(inputMan.GetOldMousePos() - inputMan.GetMousePos());
		cam.SetPos(cam.GetPos() + newCamPos);
	}
	else {
		inputMan.UpdateOldMousePos();
	}
	if (inputMan.GetKey(CONTROL) && inputMan.GetKeyDown(S)) { //TODO - actually save the game
		window.setTitle(editorScene->sceneName);
	}
	if (inputMan.GetKey(CONTROL) && inputMan.GetKeyDown(D)) { // Duplicating object
		new Object(selectedObj->GetSaveData());
	}
	if (inputMan.GetKeyDown(DELETEKEY)) { // Deleting object
		DeleteObject(selectedObj);
		selectedObj = nullptr;
	}
	if (inputMan.GetKeyDown(MOUSE_L)) { // Object selection functionality

		bool ableToDeselectObj = true; // set this to false when selecting an object to prevent a nullrefex
		for (auto& obj : objects) {
			if (((EditorItem*)obj->GetComponent(EDITOR_ITEM))->HoveringOver() && moveTool.GetCurrentMode() == MOVEMODE_IDLE) {
				inputMan.buttonMan.AddButtonCall(EDITOR_UI, ((EditorItem*)obj->GetComponent(EDITOR_ITEM))->OnClick);
				ableToDeselectObj = false;
			}
		}
		if (selectedObj && ableToDeselectObj) {
			std::function<void()> func = std::bind(&SceneEditor::ClearSelectedObj, this);
			inputMan.buttonMan.AddButtonCall(EDITOR_UI, func);
		}
	}
	inputMan.buttonMan.UpdateButtonCalls();
}

void SceneEditor::Render()
{
	window.clear();
	window.setView(cam.GetView());
	window.draw(gridSprite); // replace this with grid component

	for (auto& obj : objects) {
		obj->Render(window);
	}
	//hierarchy.Render(window);//temp turned off bc its incomplete and in the way
	moveTool.Render(window);
	window.display();
}


void SceneEditor::AddObject(Object* o)
{
	markedForAddition.push_back(o);
}
void SceneEditor::DeleteObject(Object* o)
{
	markedForDeletion.push_back(o);
}

void SceneEditor::UpdateObjectsVector()
{
	// Adds or deletes objects before updating them to prevent nullrefex
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
	if (selectedObj) {
		((EditorItem*)selectedObj->GetComponent(EDITOR_ITEM))->SetSelected(false);
	}
	selectedObj = obj; //sets new selected object
	((EditorItem*)selectedObj->GetComponent(EDITOR_ITEM))->SetSelected(true);
}

Object*& SceneEditor::GetSelectedObj()
{
	return selectedObj;
}

void SceneEditor::ClearSelectedObj()
{
	if (selectedObj) {
		((EditorItem*)selectedObj->GetComponent(EDITOR_ITEM))->SetSelected(false);
	}
	selectedObj = nullptr;
}

Camera& SceneEditor::GetCamera()
{
	return cam;
}

//void SceneEditor::LoadScenes()
//{
//	for (const auto& entry : fs::directory_iterator(scenePath)) {
//		std::string filepath = entry.path().string();
//
//		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0))
//		{
//			allScenes.emplace_back(filepath);
//			std::cout << "file found!: " << filepath << "\n";
//		}
//	}
//}
//void SceneEditor::DebugScenes()
//{
//	int numOfScenes = allScenes.size();
//	if (numOfScenes == 0) {
//		std::cout << "No levels found in: " << scenePath << "\n";
//		return;
//	}
//	numOfScenes == 1 ? std::cout << numOfScenes << " Level found at: " << scenePath << "\n" : std::cout << numOfScenes << " Levels found at: " << scenePath << "\n";
//	std::cout << "\n[-----------------------------------------------]\n";
//	for (int i = 0; i < allScenes.size(); i++) {
//		Scene& scene = allScenes[i];
//		std::cout << "Level [" << i << "]  " << scene.sceneName << "\n";
//	}
//	std::cout << "[-----------------------------------------------]\n";
//}

//void SceneEditor::OpenEditorConsole()
//{
//	LoadScenes();
//	DebugScenes();
//
//	bool loadFirstLevel = true;
//	if (loadFirstLevel) {
//		currentScene = &allScenes[0];
//		OpenEditorWindow();
//	}
//	else {
//		while (input != "exit") {
//			std::cin >> input;
//			CheckInput();
//		}
//	}
//}
// 
//void SceneEditor::CheckInput()
//{
//	//make the input lower case
//	for (char& c : input) {
//		c = std::tolower(static_cast<unsigned char>(c));
//	}
//	//check if input is name or index of level
//	for (int i = 0; i < allScenes.size(); i++) {
//		Scene& scene = allScenes[i];
//		if (input == std::to_string(i) || input == scene.sceneName) {
//			currentScene = &scene;
//			OpenEditorWindow();
//			return;
//		}
//	}
//	if (input == "help") {
//		std::cout << "'[i]' Index of level to open level\n";
//		std::cout << "'name' Name of level to open level\n";
//		std::cout << "'levels' Debug all levels found\n";
//		std::cout << "'exit' Exit the editor\n";
//		return;
//	}
//	if (input == "levels") {
//		DebugScenes();
//		return;
//	}
//	if (input == "exit"){
//		std::cout << "Exited level editor\n";
//		return;
//	}
//	std::cout << "'" << input << "' Is not a valid command \n";
//}