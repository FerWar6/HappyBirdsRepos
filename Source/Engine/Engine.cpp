#include "Engine.h"
#include "Objects/Object.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Objects/Components/RectRigidbody.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/Button.h"
#include "Objects/Components/Launcher.h"
#include "Objects/Components/SceneSelectButton.h"
#include "Objects/Components/TextRenderer.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Managers/ServiceLocator.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

Engine::Engine()
	: preLoader(),
	inputManager(),
	currentScene(nullptr),
	window(nullptr)
{
	sl::SetEngine(this);
	preLoader.buttonFunctions.LinkButtonFunctions(this);
	LoadScenes();
}

void Engine::Start()
{
	window = &sl::GetWindow();
	LoadScene("StartMenu");
	//LoadScene("level1");
	//LoadScene("MainMenu");
	//{
	//	new Object(sf::Vector2f(150, 700), 90, sf::Vector2f(600, 600));
	//	sf::Vector2f scale(1.5, 1.5);
	//	SpriteRenderer* ren = new SpriteRenderer("LauncherStand", scale, sf::Vector2f(25, 6));
	//	ren->lockRotation = true;
	//	new SpriteRenderer("Launcher", scale, sf::Vector2f(13, 87));
	//	new Launcher("PreviewDot", 2);
	//}
	//{
	//	Object* obj = new Object(sf::Vector2f(200, 200));
	//	new SpriteRenderer("LevelSelectButton", true);
	//	new Button(ButtFuncId::MOVE_TO_SCENE);
	//	std::cout << obj->GetSaveData() << "\n";
	//}
}

void Engine::Update()
{
	inputManager.SetMousePos(*window);
	inputManager.UpdateInputs();
	for (auto obj : objects) {
		obj->Update();
	}
}

void Engine::FixedUpdate()
{
	for (auto& obj : objects) {
		obj->FixedUpdate();
	}
}

void Engine::UpdateObjectsVector()
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

void Engine::AddObject(Object* o)
{
	markedForAddition.push_back(o);
}

void Engine::DeleteObject(Object* o)
{
	markedForDeletion.push_back(o);
}

PreLoader& Engine::GetPreLoader()
{
	return preLoader;
}

//LevelManager& Engine::GetLevelManager()
//{
//	return levelManager;
//}

InputManager& Engine::GetInputManager()
{
	return inputManager;
}

void Engine::LoadScenes()
{
	for (const auto& entry : fs::directory_iterator(scenePath)) {
		std::string filepath = entry.path().string();

		if (filepath.size() >= 4 && (filepath.compare(filepath.size() - 4, 4, ".txt") == 0))
		{
			allScenes.emplace_back(filepath);
			std::cout << "Scene found: " << filepath << "\n"; //allScenes[allScenes.size() - 1].sceneName << 
		}
	}
}

void Engine::ClearCurrentScene()
{
	if (objects.size() > 0) {
		markedForDeletion.insert(markedForDeletion.end(), objects.begin(), objects.end());
		objects.clear();
	}
}

void Engine::LoadScene(std::string name)
{
	//this prevents the game from loading the same scene twice, but there could be functionality to reload a scene
	Scene* newScene = GetScene(name);
	if (newScene != currentScene) {
		ClearCurrentScene();
		newScene->LoadScene();
		currentScene = newScene;
		std::cout << "entered scene: " << newScene->sceneName << "\n";
	}
}

void Engine::OpenSceneSelection()
{
	LoadScene("SceneSelect");

	sf::Vector2f basePos(750, 150);
	int margin = 50 + 10;
	for (auto& scene : allScenes) {
		Object* obj = new Object(basePos);
		obj->AddComponent<SpriteRenderer>("SceneSelectionButton", true);
		obj->AddComponent<TextRenderer>("goofy", scene.sceneName);
		obj->AddComponent<SceneSelectButton>(scene);
		basePos.y += margin;
	}
}

void Engine::OpenSceneEditor(Scene scene)
{
	window->setVisible(false);
	inEditMode = true;
	SceneEditor editor(scene);
	inEditMode = false;
	window->setVisible(true);
	LoadScene("level2");
	{
		Object* obj = new Object(sf::Vector2f(150, 700), 90, sf::Vector2f(600, 600));
		sf::Vector2f scale(1.5, 1.5);
		SpriteRenderer* ren = obj->AddComponent<SpriteRenderer>("LauncherStand", scale, sf::Vector2f(25, 6));
		ren->lockRotation = true;
		obj->AddComponent<SpriteRenderer>("Launcher", scale, sf::Vector2f(13, 87));
		obj->AddComponent<Launcher>("PreviewDot", 2);
	}
}

Scene* Engine::GetScene(std::string name)
{
	for (auto& scene : allScenes) {
		if (scene.sceneName == name) {
			return &scene;
		}
	}
}
