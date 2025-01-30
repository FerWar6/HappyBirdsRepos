#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level/Level.h"
#include "DataTypes/Camera.h"

class Object;
class InputManager;
class LevelEditor
{
public:
	// the editor needs no update for the components, 
	// just an ability to render the objects
	LevelEditor(InputManager& inputMan, LevelEditor* selfPtr);

	sf::Sprite moveWidgetSprite;
	sf::Sprite gridSprite;
	void OpenEditorConsole();
	void OpenEditorWindow();
	void CheckInput();
	std::vector<Object*> objects;
	std::vector<Object*> markedForAddition;
	std::vector<Object*> markedForDeletion;
	void UpdateObjectsVector();
	void SetSelectedObj(Object* obj);
	void ClearSelectedObj();
private:
	void Update();
	void FixedUpdate();
	void UpdateInput();

	void Render();
	InputManager& inputMan;
	Object* selObj; // the selected object in the editor
	Level* currentLevel;
	void LoopEditor();
	void LoadLevels();
	void DebugLevels();
	std::string input;
	std::vector<Level> allLevels;
	std::string levelPath = "Assets/Levels/";

	Camera cam;
	sf::RenderWindow window;
	sf::Clock gameClock;

	int fixedUpdateFrames = 60;
	const float timeStep = 1.0f / fixedUpdateFrames;
	float deltTime = 0.0f;
	float accumulator = 0.0f;
};