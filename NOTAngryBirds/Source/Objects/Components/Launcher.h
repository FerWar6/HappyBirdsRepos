#pragma once
#include "Objects/Components/Component.h"
#include "Objects/Object.h";
#include <functional>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
class InputManager;

class Launcher : public Component
{
public:
	Launcher(std::string txrName);
	void Update() override;
	void FixedUpdate() override;
	void Render(sf::RenderWindow& window) override;
	sf::Sprite dotSprite;

	std::string GetSaveData() override;
private:
	InputManager& inputMan;

	float buttonMinRadius;
	float buttonMaxRadius;
	float minVelocity;
	float maxVelocity;
	float minAngle;
	float maxAngle;
	bool primed;

	void SpawnProjectile();
	bool HoveringOver(float min, float max = 0);


	float CalcAngle();
	bool IsAngleValid();
	float CalcDistanceToMouse();
	float CalcInvalidAngleDistance();
	float CalcVelocity();
	b2Vec2 CalcLinearVelocity();
	sf::Vector2f CalcLaunchPoint();


	float spriteRotationalOffset = 90;
	float moveSpeed;

	void MoveBackToBasePos();

	int amountOfDots;
	std::vector<sf::Vector2f> dotPositions;

	void UpdatePreview();
	void SetPreview(float angle, float velocity, sf::Vector2f previewPos);
	void DrawPreview(sf::RenderWindow& window);
	float GetXWidth(float angle, float velocity, int amountOfDots, float arcLenght);
	double GetArchLength(double x, float angle, float velocity);
};