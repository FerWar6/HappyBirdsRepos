#pragma once
#include "Objects/Components/Component.h"
#include "SFML/Graphics.hpp"
class DestructibleItem : public Component
{
public:
	DestructibleItem(float health);
	void Damage(float dmg);
private:
	float maxHealth;
	float curHealth;
	void DestroyItem();
};