#include "SpriteRenderer.h"
#include "Objects/Object.h"
SpriteRenderer::SpriteRenderer(sf::Texture& txrRef)
	: Component("SpriteRenderer")
{
	//add ability to resezise or to keep size of texture
	sprite.setPosition(object->GetPos());

	sprite.setTexture(txrRef);

	//the scale is the object size devided by the size of the texture on both x and y
	sf::Vector2f scale;
	scale.x =  object->GetSize().x / txrRef.getSize().x;
	scale.y =  object->GetSize().y / txrRef.getSize().y;
	sprite.setScale(scale);
	
	sf::Vector2f origin((float)(txrRef.getSize().x / 2), (float)(txrRef.getSize().y / 2));
	sprite.setOrigin(origin);

	//sprite width devided by 2
}

void SpriteRenderer::Render(sf::RenderWindow& window)
{
	if (sprite.getPosition().x != object->GetPos().x || sprite.getPosition().y != object->GetPos().y)
	{
		sprite.setPosition(object->GetPos());
		sprite.setRotation(object->GetRot());
	}
	window.draw(sprite);
}

