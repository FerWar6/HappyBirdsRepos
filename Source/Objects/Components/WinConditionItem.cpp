#include "WinConditionItem.h"

WinConditionItem::WinConditionItem(int scoreValue)
	:	Component(WINCONDITION_ITEM),
	score(scoreValue)
{
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
