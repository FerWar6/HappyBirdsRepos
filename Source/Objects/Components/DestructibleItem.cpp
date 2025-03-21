#include "DestructibleItem.h"

DestructibleItem::DestructibleItem(float health)
    : Component(DESTRUCTIBLE_ITEM),
    curHealth(health),
    maxHealth(health)
{}

void DestructibleItem::Damage(float dmg)
{
    if (curHealth - dmg >= 0) {
        curHealth -= dmg;
        std::cout << "Damaged item " << dmg << "\n";
    }
    else
    {
        DestroyItem();
    }
}

void DestructibleItem::DestroyItem()
{
    std::cout << "Destroyed item \n";
}