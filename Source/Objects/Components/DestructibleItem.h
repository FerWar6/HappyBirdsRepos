#pragma once
#include "Objects/Components/Component.h"
#include "SFML/Graphics.hpp"
class DestructibleItem : public Component
{
	// This component makes a body destructable
public:
	DestructibleItem(float health);
	void Damage(float dmg);
	void DamageWithSpeed(float speed);
	std::string GetSaveData() override;
private:
	float maxHealth;
	float curHealth;
	void DestroyItem();
};