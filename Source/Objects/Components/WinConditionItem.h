#pragma once
#include "Objects/Components/Component.h"
class WinConditionItem : public Component
{
public:
	WinConditionItem(int scoreValue);
	~WinConditionItem();
	void Update() override;
	std::string GetSaveData() override;
private:
	int score; //the score the player will earn when killing this winCondition
};
