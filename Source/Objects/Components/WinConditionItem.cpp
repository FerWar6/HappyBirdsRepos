#include "WinConditionItem.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Managers/GameManager.h"
WinConditionItem::WinConditionItem(int scoreValue)
	:	Component(WINCONDITION_ITEM),
	score(scoreValue)
{
    sl::GetEngine().GetGameManager().AddWinObject(&object);
}

WinConditionItem::~WinConditionItem()
{
    //do end level check
}

void WinConditionItem::Update()
{
}

std::string WinConditionItem::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(score) + " ";
    return data;
}
