#include "CameraPan.h"
#include "Managers/ServiceLocator.h"
#include "Managers/GameManager.h"
#include "Engine/Engine.h"
CameraPan::CameraPan()
	: Component(CAMERA_PAN)
{
	sl::GetEngine().GetGameManager().SetCameraPan(&object);
}

std::string CameraPan::GetSaveData()
{
	std::string data;
	data += std::to_string(type) + " ";
	return data;
}
