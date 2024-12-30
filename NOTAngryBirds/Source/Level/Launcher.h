#pragma once
#include "Objects/Object.h";

class Launcher : public Object
{
public:
	Launcher();
	void Update() override;
	void FixedUpdate() override;
	void Render(sf::RenderWindow& window) override;
private:
	sf::Sprite standSprite;
	sf::Sprite launcherSprite;
};