#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DataTypes/Camera.h"
#include "UI/Hierarchy.h"
#include "UI/EditorMoveTool.h"
#include "Engine/Scenes/Scene.h"
class Object;
class InputManager;

class SceneEditor
{
public:
	SceneEditor(Scene& scene);
	~SceneEditor();
	sf::Sprite gridSprite;
	void OpenEditorWindow();

	std::vector<Object*> objects;
	std::vector<Object*> markedForAddition;
	std::vector<Object*> markedForDeletion;
	void AddObject(Object* obj);
	void DeleteObject(Object* obj);

	void UpdateObjectsVector();
	void SetSelectedObj(Object* obj);
	Object*& GetSelectedObj();
	void ClearSelectedObj();
	Camera& GetCamera();
private:
	void Update();

	void Render();
	InputManager& inputMan;
	Object* selectedObj; // the selected object in the editor
	Scene* currentScene;
	void LoopEditor();
	void LoadScenes();
	std::vector<Scene> allScenes;
	std::string scenePath = "Assets/Scenes/";

	Hierarchy hierarchy;
	EditorMoveTool moveTool;
	Camera cam;
	sf::RenderWindow window;
	sf::Clock gameClock;

	int fixedUpdateFrames = 60;
	const float timeStep = 1.0f / fixedUpdateFrames;
	float deltTime = 0.0f;
	float accumulator = 0.0f;

	//void OpenEditorConsole();
	//void CheckInput();
	//void DebugScenes();
	//std::string input;
};