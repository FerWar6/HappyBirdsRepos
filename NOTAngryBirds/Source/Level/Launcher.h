#pragma once
#include "Objects/Object.h";

class Launcher : public Object
{
public:
	Launcher();
	void Update() override;
	void FixedUpdate() override;
	void Render(sf::RenderWindow& window) override;
	sf::Vector2f GetLaunchPoint();
	float GetLauncherAngle();
	float GetLaunchDistance();
	b2Vec2 GetLaunchMomentum();
private:
	sf::Sprite standSprite;
	sf::Sprite launcherSprite;
	sf::Sprite ringSprite;
};