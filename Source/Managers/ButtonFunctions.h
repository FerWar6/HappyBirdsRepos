#pragma once
#include <functional>
#include <vector>
class Engine;

enum ButtFuncId {
	MOVE_TO_SCENE,
	MOVE_TO_SCENE_SELECTION,
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
public:
	ButtonFunctions() {};
	void LinkButtonFunctions(Engine* engine);
	//TODO - figure out if there is a way to pass the function by referance instead of using the copy constructor
	std::function<void()> GetButtonFunction(ButtFuncId functionId) {
		for (auto func : buttonFunctions) {
			if (func.id == functionId) {
				return func.GetFunction();
			}
		}
	}
	std::vector<ButtonFunction> buttonFunctions;
};