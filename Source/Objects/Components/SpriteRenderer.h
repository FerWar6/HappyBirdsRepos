#pragma once
#include "Objects/Components/Component.h"
#include <SFML/Graphics.hpp>
class SpriteRenderer : public Component
{
public:
	SpriteRenderer(std::string txrName);
	SpriteRenderer(std::string txrName, bool useOwnSize, bool lockRotation = false , sf::Vector2f origin = sf::Vector2f(0, 0));

	void Render(sf::RenderWindow& window) override;

	sf::Vector2f GetScale();
	sf::Vector2f GetOrigin();
	void SetOrigin(sf::Vector2f origin);
	void SetOrigin(float x, float y);

	void SetColor(sf::Color& col);
	std::string GetSaveData() override;

private:
	void Start(sf::Texture& txrRef, sf::Vector2f origin);
	sf::Sprite sprite;
	std::string txrName;

	bool lockRotation;
	bool useOwnSize;
	sf::Vector2f GetOriginFromTxr(sf::Vector2u txrSize);
	bool UseSizeCheck(sf::Vector2f& size); //prevents sprites from being 1,1   the object default is 1,1 and if it isnt changed the sprite cant be seen
};