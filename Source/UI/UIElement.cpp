#include "UIElement.h"
#include "Managers/ServiceLocator.h"
#include "Level/LevelEditor.h"
UIElement::UIElement()
	: cam(sl::GetLevelEditor().GetCamera())
{
	sl::GetLevelEditor().AddUI(this);
}
