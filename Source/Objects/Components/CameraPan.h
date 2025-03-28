#pragma once
#include "Objects/Components/Component.h"
class CameraPan : public Component
{
public:
	CameraPan();

	std::string GetSaveData() override;
private:

};