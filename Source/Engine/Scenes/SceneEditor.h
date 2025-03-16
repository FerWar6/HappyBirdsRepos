#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DataTypes/Camera.h"
#include "Engine/Scenes/Scene.h"
class Object;
class UIElement;
class InputManager;
class SceneEditor
{
public:
	SceneEditor(Scene& scene);

	sf::Sprite moveWidgetSprite;
	sf::Sprite gridSprite;
	void OpenEditorConsole();
	void OpenEditorWindow();
	void CheckInput();

	std::vector<Object*> objects;
	std::vector<Object*> markedForAddition;
	std::vector<Object*> markedForDeletion;
	void AddObject(Object* obj);
	void DeleteObject(Object* obj);

	std::vector<UIElement*> uiElements;
	void AddUI(UIElement* ui);

	void UpdateObjectsVector();
	void SetSelectedObj(Object* obj);
	Object* GetSelectedObj();
	void ClearSelectedObj();
	Camera& GetCamera();
private:
	void Update();
	//void FixedUpdate();
	void UpdateInput();

	void Render();
	InputManager& inputMan;
	Object* selObj; // the selected object in the editor
	Scene* currentScene;
	void LoopEditor();
	void LoadScenes();
	void DebugScenes();
	std::string input;
	std::vector<Scene> allScenes;
	std::string scenePath = "Assets/Scenes/";

	Camera cam;
	sf::RenderWindow window;
	sf::Clock gameClock;

	int fixedUpdateFrames = 60;
	const float timeStep = 1.0f / fixedUpdateFrames;
	float deltTime = 0.0f;
	float accumulator = 0.0f;
};