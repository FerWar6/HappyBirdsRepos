#include "Launcher.h"
#include "Engine/PreLoader.h"
#include "Engine/Engine.h"
#include "Managers/InputManager.h"
Launcher::Launcher()
	: Object()
{
	sf::Texture& standTxr = manager->preLoaderPtr->GetTexture("LauncherStand");
	sf::Texture& launcherTxr = manager->preLoaderPtr->GetTexture("Launcher");
	standSprite.setTexture(standTxr);
	launcherSprite.setTexture(launcherTxr);
	standSprite.setPosition(sf::Vector2f(50, 50));
	launcherSprite.setPosition(sf::Vector2f(100, 50));
	sf::Vector2f scale(1.5,1.5);
	standSprite.setScale(scale);
	launcherSprite.setScale(scale);
}

void Launcher::Update()
{
}

void Launcher::FixedUpdate()
{
}

void Launcher::Render(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = manager->enginePtr->GetInputManager().cursorPos;
	launcherSprite.setPosition((sf::Vector2f)mousePos);
	window.draw(launcherSprite);
	window.draw(standSprite);

	sf::Vertex line[] =
	{
		sf::Vertex(launcherSprite.getPosition()),
		sf::Vertex(standSprite.getPosition())
	};

	window.draw(line, 2, sf::Lines);
}
