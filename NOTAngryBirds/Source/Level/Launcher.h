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
	float GetLaunchVelocity();
	b2Vec2 GetLaunchMomentum();
private:
	float GetXWidth(float angle, float velocity, int amountOfDots, float arcLenght);
	void DrawPreview(sf::RenderWindow& window);
	sf::Sprite standSprite;
	sf::Sprite launcherSprite;
	sf::Sprite ringSprite;
	sf::Sprite previewDotSprite;
	double GetArchLength(double x, float angle, float velocity);
};