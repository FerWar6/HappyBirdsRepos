#include "Launcher.h"
#include "Engine/PreLoader.h"
#include "Engine/Engine.h"
#include "Managers/InputManager.h"
Launcher::Launcher()
	: Object()
{
	
	sf::Texture& standTxr = manager->preLoaderPtr->GetTexture("LauncherStand");
	sf::Texture& launcherTxr = manager->preLoaderPtr->GetTexture("Launcher");
	sf::Texture& ringTxr = manager->preLoaderPtr->GetTexture("LauncherRing");
	standSprite.setTexture(standTxr);
	launcherSprite.setTexture(launcherTxr);
	ringSprite.setTexture(ringTxr);
	sf::Vector2f pos(300, 500);
	standSprite.setPosition(pos);
	launcherSprite.setPosition(pos);
	sf::Vector2f scale(1.5,1.5);
	standSprite.setScale(scale);
	launcherSprite.setScale(scale);
	standSprite.setOrigin(sf::Vector2f(25, 6));
	launcherSprite.setOrigin(sf::Vector2f(13, 87));
	ringSprite.setOrigin(ringTxr.getSize().x/2, ringTxr.getSize().y / 2);
	ringSprite.setPosition(launcherSprite.getPosition());
}

void Launcher::Update()
{
}

void Launcher::FixedUpdate()
{
	//launcherSprite.setRotation(launcherSprite.getRotation() + 1);
}

void Launcher::Render(sf::RenderWindow& window)
{

	launcherSprite.setRotation(GetLauncherAngle() + 90);
	window.draw(launcherSprite);
	window.draw(standSprite);
	ringSprite.setScale(sf::Vector2f(.75,.75));
	window.draw(ringSprite);
	ringSprite.setScale(sf::Vector2f(2, 2));
	window.draw(ringSprite);

	sf::Vector2f pos;
	float distance = GetLaunchDistance();
	float radians = GetLauncherAngle() / 180 * 3.14159f;
	pos.x = distance * cos(radians) + launcherSprite.getPosition().x;
	pos.y = distance * sin(radians) + launcherSprite.getPosition().y;

	sf::Vertex line[] =
	{
		sf::Vertex(pos),
		sf::Vertex(GetLaunchPoint())
	};

	window.draw(line, 2, sf::Lines);
}

sf::Vector2f Launcher::GetLaunchPoint()
{
	sf::Vector2 launcherPos(launcherSprite.getPosition());
	float offset = 0;
	float radians = (GetLauncherAngle() + offset) / 180 * 3.14159f;
	sf::Vector2f pos;
	float distance = 130;
	pos.x = distance * cos(radians) + launcherPos.x;
	pos.y = distance * sin(radians) + launcherPos.y;
	return pos;
}

float Launcher::GetLauncherAngle()
{
	sf::Vector2i mousePos = manager->enginePtr->GetInputManager().cursorPos;
	sf::Vector2 launcherPos(launcherSprite.getPosition());
	float angle = atan2(launcherPos.y - mousePos.y, launcherPos.x - mousePos.x);
	angle = angle * 180 / 3.14159f;
	return angle;
}

float Launcher::GetLaunchDistance()
{
	sf::Vector2i mousePos = manager->enginePtr->GetInputManager().cursorPos;
	sf::Vector2f launchPoint(GetLaunchPoint());
	float distance = sqrt(pow(launchPoint.x - mousePos.x, 2) + pow(launchPoint.y - mousePos.y, 2) * 1.0);
	float minDistance = 130;
	float maxDistance = 150;
	if (distance < minDistance) distance = minDistance;
	if (distance > maxDistance) distance = maxDistance;
	return distance;
}

b2Vec2 Launcher::GetLaunchMomentum()
{
	b2Vec2 launchMomentum;
	float distance = GetLaunchDistance();
	float radians = GetLauncherAngle() / 180 * 3.14159f;
	sf::Vector2f launchPoint = GetLaunchPoint();
	launchMomentum.x = distance * cos(radians) + launcherSprite.getPosition().x - launchPoint.x;
	launchMomentum.y = distance * sin(radians) + launcherSprite.getPosition().y - launchPoint.y;
	std::cout << "x: " << launchMomentum.x << " y: " << launchMomentum.y << "\n";
	std::cout << "GetLaunchDistance: " << distance << "\n";
	return launchMomentum;
}
