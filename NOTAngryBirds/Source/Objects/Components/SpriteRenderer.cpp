#include "SpriteRenderer.h"
#include "Objects/Object.h"
SpriteRenderer::SpriteRenderer(Object& obj, sf::Texture& txrRef)
	: Component(obj, "SpriteRenderer")
{
	sprite.setPosition(object.GetPos());
	//sprite.setPosition(sf::Vector2f(0,0));
	sprite.setTexture(txrRef);
	//get the x size of the texture and devide it by the size of the object
	sf::Vector2f scale;
	scale.x =  object.GetSize().x / txrRef.getSize().x;
	scale.y =  object.GetSize().y / txrRef.getSize().y;
	sprite.setScale(scale);
	//this is hardcoded for some reason
	sprite.setOrigin(object.GetSize().x / 2, object.GetSize().y / 2);
	std::cout << "\n" << "Component: "  << "\n";
	std::cout << "size.x: " << object.GetSize().x << "\n";
	std::cout << "size.y: " << object.GetSize().y << "\n";
	sprite.setOrigin(sf::Vector2f(25, 25));
	//sprite.setOrigin(sf::Vector2f(25, 50));
}

void SpriteRenderer::Render(sf::RenderWindow& window)
{
	if (sprite.getPosition().x != object.GetPos().x || sprite.getPosition().y != object.GetPos().y)
	{
		sprite.setPosition(object.GetPos());
		sprite.setRotation(object.GetRot());
	}
	window.draw(sprite);
}

