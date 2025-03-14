#pragma once
class Engine;
class SceneEditor;
class PreLoader;
class InputManager;
namespace sf { class RenderWindow; }
class b2WorldId;
class Object;

namespace ServiceLocator {

	inline Engine* engine = nullptr;
	inline Engine& GetEngine() { return *engine; }
	inline void SetEngine(Engine* eng) { engine = eng; }

	inline SceneEditor* sceneEditor = nullptr;
	inline SceneEditor& GetSceneEditor() { return *sceneEditor; }
	inline void SetSceneEditor(SceneEditor* se) { sceneEditor = se; }

	inline PreLoader* preLdr = nullptr;
	inline PreLoader& GetPreLoader() { return *preLdr; }
	inline void SetPreLoader(PreLoader* pl) { preLdr = pl; }

	inline InputManager* inputMan = nullptr;
	inline InputManager& GetInputManager() { return *inputMan; }
	inline void SetInputManager(InputManager* inp) { inputMan = inp; }

	inline sf::RenderWindow* window = nullptr;
	inline sf::RenderWindow& GetWindow() { return *window; }
	inline void SetWindow(sf::RenderWindow* win) { window = win; }

	inline b2WorldId* worldId = nullptr;
	inline b2WorldId& GetWorldId() { return *worldId; }
	inline void SetWorldId(b2WorldId* id) { worldId = id; }

	// If you select an object and create a component, the component will add itself to the selected object
	// The object will automatically set itself as the selected object unless you set the parameter in its constructor as false

	inline Object* selectedObj = nullptr;
	inline Object& GetSelectedObj() { return *selectedObj; }
	inline void SetSelectedObj(Object* obj) { selectedObj = obj; }
}

namespace sl = ServiceLocator;