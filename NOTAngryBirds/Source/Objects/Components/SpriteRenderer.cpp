#include "SpriteRenderer.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"

//this constructor is for adding a sprite to a rigidbody
//it automatically sets the scale of the rigidbody and the orgin
SpriteRenderer::SpriteRenderer(std::string txrNm)
	: Component(ComponentType::SPRITE_RENDERER),
	txrName(txrNm),
	useOwnSize(false),
	lockRotation(false)
{
	sf::Texture& txrRef = sl::GetPreLoader()->GetTexture(txrNm);
	//the scale is the object size devided by the size of the texture on both x and y
	sf::Vector2f scale;
	scale.x = object->GetSize().x / txrRef.getSize().x;
	scale.y = object->GetSize().y / txrRef.getSize().y;

	Start(txrRef, scale, GetOriginFromTxr(txrRef.getSize()));
}
//this constructor is for adding a sprite to a button
SpriteRenderer::SpriteRenderer(std::string txrNm, bool useSize)
	: Component(ComponentType::SPRITE_RENDERER),
	txrName(txrNm),
	useOwnSize(useSize),
	lockRotation(false)
{
	sf::Texture& txrRef = sl::GetPreLoader()->GetTexture(txrNm);
	//the scale is the object size devided by the size of the texture on both x and y
	sf::Vector2f scale(1, 1);
	Start(txrRef, scale, GetOriginFromTxr(txrRef.getSize()));
}

//this constructor is for adding a sprite to an object that needs more customizability
SpriteRenderer::SpriteRenderer(std::string txrNm, sf::Vector2f scale, sf::Vector2f origin)
	: Component(ComponentType::SPRITE_RENDERER),
	txrName(txrNm),
	useOwnSize(true),
	lockRotation(false)
{
	sf::Texture& txrRef = sl::GetPreLoader()->GetTexture(txrNm);
	if(origin.x == 0 && origin.y == 0) origin = GetOriginFromTxr(txrRef.getSize());
	Start(txrRef, scale, origin);
}

void SpriteRenderer::Start(sf::Texture& txrRef, sf::Vector2f scale, sf::Vector2f origin)
{
	sprite.setTexture(txrRef);
	sprite.setPosition(object->GetPos());
	sprite.setScale(scale);
	sprite.setOrigin(origin);
	if (useOwnSize) object->SetSize((sf::Vector2f)txrRef.getSize());
}

void SpriteRenderer::Render(sf::RenderWindow& window)
{
	//move if position has chaned
	if (sprite.getPosition().x != object->GetPos().x || sprite.getPosition().y != object->GetPos().y || sprite.getRotation() != object->GetRot())
	{
		sprite.setPosition(object->GetPos());
		if(!lockRotation) sprite.setRotation(object->GetRot());
	}
	window.draw(sprite);
}
Component* SpriteRenderer::GetComponentPtr()
{
	return this;
}

sf::Vector2f SpriteRenderer::GetScale()
{
	return sprite.getScale();
}

sf::Vector2f SpriteRenderer::GetOrigin()
{
	return sprite.getOrigin();
}

sf::Vector2f SpriteRenderer::GetOriginFromTxr(sf::Vector2u txrSize)
{
	return sf::Vector2f((float)(txrSize.x / 2), (float)(txrSize.y / 2));
}
