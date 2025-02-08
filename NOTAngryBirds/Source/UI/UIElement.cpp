#include "UIElement.h"
#include "Managers/ServiceLocator.h"
#include "Level/LevelEditor.h"
UIElement::UIElement()
{
	sl::GetLevelEditor().AddUI(this);
}
