#include "DestructibleItem.h"
#include "Objects/Object.h"
#include "SpriteRenderer.h"
DestructibleItem::DestructibleItem(float health)
    : Component(DESTRUCTIBLE_ITEM),
    curHealth(health),
    maxHealth(health)
{}

void DestructibleItem::Damage(float dmg)
{
    if (curHealth - dmg >= 0) { // Changes sprite alpha when damaged
        if (object.HasComponent(SPRITE_RENDERER)) {
            SpriteRenderer* spriteRen = (SpriteRenderer*)object.GetComponent(SPRITE_RENDERER);
            spriteRen->SetColor(sf::Color(255, 255, 255, 200));
        }
        curHealth -= dmg;
    }
    else
    {
        DestroyItem();
    }
}

void DestructibleItem::DamageWithSpeed(float speed) // Calculate the speed to the dmg
{
    float dmg = speed * 7.5f;
    //std::cout << "speed " << speed << "\n";
    //std::cout << "Damaged item " << dmg << "\n";
    if (curHealth - dmg >= 0) { // Changes sprite alpha when damaged
        curHealth -= dmg;
        if (object.HasComponent(SPRITE_RENDERER)) {
            SpriteRenderer* spriteRen = (SpriteRenderer*)object.GetComponent(SPRITE_RENDERER);
            int a = static_cast<int>(curHealth / maxHealth * 200) + 55;
            spriteRen->SetColor(sf::Color(255, 255, 255, a));
        }
    }
    else
    {
        DestroyItem();
    }
}

void DestructibleItem::DestroyItem()
{
    //std::cout << "Destroyed item \n";
    object.Delete(); // Adds the object pointer to markedForDeletion
}
std::string DestructibleItem::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(maxHealth) + " ";
    return data;
}