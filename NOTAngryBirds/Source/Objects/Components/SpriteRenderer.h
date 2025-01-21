#pragma once
#include "Objects/Components/Component.h"
#include "SFML/Graphics.hpp"
struct SpriteRenderer : Component
{
	SpriteRenderer(std::string txrName);
	SpriteRenderer(std::string txrName, bool useOwnSize);
	SpriteRenderer(std::string txrName, sf::Vector2f scale, sf::Vector2f origin = sf::Vector2f(0,0));
	sf::Sprite sprite;

	void Start(sf::Texture& txrRef, sf::Vector2f scale, sf::Vector2f origin);
	void Render(sf::RenderWindow& window) override;
	Component* GetComponentPtr() override;

	bool lockRotation;
	bool useOwnSize;
	sf::Vector2f GetScale();
	sf::Vector2f GetOrigin();
	sf::Vector2f GetOriginFromTxr(sf::Vector2u txrSize);
	std::string txrName; //for now this is the name of the texture because of how I set up the preloader
	//if preloader ever changes and it requires a path to the texture this will also have to change
	bool UseSizeCheck(sf::Vector2f size); //prevents sprites from bing 1,1   the object default is 1,1 and if it isnt changed the sprite cant be seen
	std::string GetSaveData() override;
};