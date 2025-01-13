#include "SpriteRenderer.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
SpriteRenderer::SpriteRenderer(std::string txrNm)
	: Component(ComponentType::SPRITE_RENDERER),
	txrName(txrNm)
{
	//add ability to resezise or to keep size of texture
	//if you dont have a box collider, make the object the size of the sprite
	sf::Texture& txrRef = sl::GetPreLoader()->GetTexture(txrNm);
	sprite.setPosition(object->GetPos());
	sprite.setTexture(txrRef);
	if (object->GetSize().x == 1 && object->GetSize().y == 1) {
		//use size of sprite
		object->SetSize((sf::Vector2f)txrRef.getSize());
	}
	else
	{
		//the scale is the object size devided by the size of the texture on both x and y
		sf::Vector2f scale;
		scale.x = object->GetSize().x / txrRef.getSize().x;
		scale.y = object->GetSize().y / txrRef.getSize().y;
		sprite.setScale(scale);
	}
	sf::Vector2f origin((float)(txrRef.getSize().x / 2), (float)(txrRef.getSize().y / 2));
	sprite.setOrigin(origin);

	//sprite width devided by 2
}

Component* SpriteRenderer::GetComponentPtr()
{
	return this;
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