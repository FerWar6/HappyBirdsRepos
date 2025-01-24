#include "ButtonFunctions.h"
#include "Engine/Engine.h"
#include "Level/LevelEditor.h"
void ButtonFunctions::LinkButtonFunctions(Engine* engine, LevelEditor* editor)
{
	int numOfFunc = static_cast<int>(ButtFuncId::BUTTON_FUNCTIONS_COUNT);
	for (int i = 0; i < numOfFunc; i++) {
		ButtFuncId currentFunc = ButtFuncId(i);
		switch (currentFunc) {
		case MOVE_TO_SCENE:
			buttonFunctions.emplace_back(currentFunc, std::bind(&Engine::LoadScene, engine, "LevelSelectMenu"));
			break;
		case SELECT_IN_EDITOR:
			buttonFunctions.emplace_back(currentFunc, std::bind(&LevelEditor::SetSelectedObject, editor));
			break;
		default:
			std::cout << "Button function is missing id";
		}
	}
}