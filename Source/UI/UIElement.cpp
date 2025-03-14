#include "UIElement.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Scenes/SceneEditor.h"
UIElement::UIElement()
	: cam(sl::GetSceneEditor().GetCamera())
{
	sl::GetSceneEditor().AddUI(this);
}
