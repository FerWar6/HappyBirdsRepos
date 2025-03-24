#include "ButtonFunctions.h"
#include "Engine/Engine.h"
#include "Engine/Scenes/SceneEditor.h"
void ButtonFunctions::LinkButtonFunctions(Engine* engine)
{
	int numOfFunc = static_cast<int>(ButtFuncId::BUTTON_FUNCTIONS_COUNT);
	for (int i = 0; i < numOfFunc; i++) {
		ButtFuncId currentFunc = ButtFuncId(i);
		switch (currentFunc) {
		case LOADSCENE_LEVELSELECT:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::LoadScene, engine, "level2 - Copy"));
			break;
		case LOADSCENE_SCENESELECT:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::OpenSceneSelection, engine));
			break;
		case LOADSCENE_MAINMENU:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::LoadScene, engine, "MainMenu"));
			break;
		default:
			std::cout << "Button function is missing id";
		}
	}
}