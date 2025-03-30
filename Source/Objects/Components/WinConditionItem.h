#pragma once
#include "Objects/Components/Component.h"
class WinConditionItem : public Component
{
	// TODO - change this component to just add score and have a bool determain if it is a wincondition
public:
	WinConditionItem(int scoreValue);
	~WinConditionItem();
	void Update() override;
	bool IsMoving();
	std::string GetSaveData() override;
private:
	int score; //the score the player will earn when killing this winCondition
};
