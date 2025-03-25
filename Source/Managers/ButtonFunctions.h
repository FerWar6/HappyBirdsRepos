#pragma once
#include <functional>
#include <vector>
class Engine;
class GameManager;
enum ButtFuncId {
	LOADSCENE_LEVELSELECT,
	LOADSCENE_SCENESELECT,
	LOADSCENE_MAINMENU,
	LOADSCENE_NEXTLEVEL,
	BUTTON_FUNCTIONS_COUNT
};
struct ButtonFunction {
	ButtonFunction(ButtFuncId id, std::function<void()> func)
		: id(id),
	function(func) {}

	ButtFuncId id;
	std::function<void()> GetFunction() {
		return function;
	}
private:
	std::function<void()> function;
};

class SceneEditor;

class ButtonFunctions
{
	// Button functions are used to store the function of a button inside of an enum so it can be saved as characters in a text file
public:
	ButtonFunctions() {};
	void LinkButtonFunctions(Engine* engine, GameManager* gameMan); // Links all of the functions
	std::function<void()> GetButtonFunction(ButtFuncId functionId) {
		for (auto func : buttonFunctions) {
			if (func.id == functionId) {
				return func.GetFunction();
			}
		}
	}
	std::vector<ButtonFunction> buttonFunctions;
};