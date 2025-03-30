#include "ButtonFunctions.h"
#include "Engine/Engine.h"
#include "Engine/Scenes/SceneEditor.h"
void ButtonFunctions::LinkButtonFunctions(Engine* engine, GameManager* gameMan)
{
	int numOfFunc = static_cast<int>(ButtFuncId::BUTTON_FUNCTIONS_COUNT);
	for (int i = 0; i < numOfFunc; i++) {
		ButtFuncId currentFunc = ButtFuncId(i);
		switch (currentFunc) {
		case LOADSCENE_LEVELSELECT:
			buttonFunctions.emplace_back(currentFunc, std::bind(&GameManager::OpenLevelSelection, gameMan));
			break;
		case LOADSCENE_SCENESELECT:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::OpenSceneSelection, engine));
			break;
		case LOADSCENE_MAINMENU:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::LoadScene, engine, "MainMenu"));
			break;
		case LOADSCENE_CURRENTLEVEL:
			buttonFunctions.emplace_back(currentFunc, std::bind(&GameManager::LoadLevelWithIndex, gameMan));
			break;
		case QUITGAME:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::Quit, engine));
			break;
		default:
			std::cout << "Button function is missing id";
		}
	}
}