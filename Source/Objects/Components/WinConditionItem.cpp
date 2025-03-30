#include "WinConditionItem.h"
#include "Managers/ServiceLocator.h"
#include "Engine/Engine.h"
#include "Managers/GameManager.h"
#include "Objects/Object.h"
#include "Objects/Components/Components.h"
WinConditionItem::WinConditionItem(int scoreValue)
	:	Component(WINCONDITION_ITEM),
	score(scoreValue)
{
    sl::GetEngine().GetGameManager().AddWinObject(this);
}

WinConditionItem::~WinConditionItem()
{
    sl::GetEngine().GetGameManager().DeleteWinObject(this);
}

void WinConditionItem::Update()
{
}

bool WinConditionItem::IsMoving()
{
    float yVelocityThreshold = 0.025f;
    float xVelocityThreshold = 0.025f;
    if (object.HasComponent(CIRCLE_RIGIDBODY)) {
        CircleRigidbody* circleBodyPtr = (CircleRigidbody*)object.GetComponent(CIRCLE_RIGIDBODY);
        b2Vec2 velocity = b2Body_GetLinearVelocity(circleBodyPtr->GetBodyId());
        if (velocity.y > yVelocityThreshold) {
            return true;
        }
        if (velocity.x > xVelocityThreshold) {
            return true;
        }
    }
    return false;
}

std::string WinConditionItem::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(score) + " ";
    return data;
}
