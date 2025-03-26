#pragma once
#include "Objects/Components/Component.h"
#include "Objects/Object.h";
#include <functional>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
class InputManager;

class Launcher : public Component
{
public:
	Launcher(int numOfAmmo); // Unique ammo count to set in scene data
	void Update() override;
	void FixedUpdate() override;
	void Render(sf::RenderWindow& window) override;

	std::string GetSaveData() override;
private:
	InputManager& inputMan;

	int maxAmmo;
	int ammoCount;

	float minRadius; // min radius of cannon
	float maxRadius; // max radius of cannon
	float minVelocity;
	float maxVelocity;
	float minAngle; // between what angle can the cannon shoot
	float maxAngle;
	bool primed;

	void SpawnProjectile();
	bool HoveringOver(float min, float max = 0); // detect if mouse is hovering over cannon


	sf::Sprite dotSprite;
	float CalcAngle(); // Calculates angle of the cannon
	bool IsAngleValid(); // returns if cannon angle is between the max and min angle
	float CalcDistanceToMouse(); // Calculates the distance between the mouse and cannon
	float CalcInvalidAngleDistance(); // Calculates what velocity to use when angle is invalid
	float CalcVelocity(); // Calculates velocity of the cannon
	b2Vec2 CalcLinearVelocity(); // Calculates the velocity of the cannon as a B2Vec2
	sf::Vector2f CalcLaunchPoint(); // Calculates the point from which the cannon should launch


	float spriteRotationalOffset = 90; //fixes sprite
	float moveSpeed; // The speed the cannon moves back at
	void MoveBackToBasePos();

	int amountOfDots; // Amount of dots in the preview
	std::vector<sf::Vector2f> dotPositions; // vector of positions of the dots

	void UpdatePreview(); // Updates the dotPositions
	void SetPreview(float angle, float velocity, sf::Vector2f previewPos); // calculates the preview
	void DrawPreview(sf::RenderWindow& window);
	float GetXWidth(float angle, float velocity, int amountOfDots, float arcLenght); // Returns the x distance between the dots
	double GetArchLength(double x, float angle, float velocity); // returns the length of the arch 
};