#include "SpriteRenderer.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"

//this constructor is for adding a sprite to a rigidbody
//it automatically sets the scale of the rigidbody and the orgin
SpriteRenderer::SpriteRenderer(std::string txrNm)
	: Component(SPRITE_RENDERER),
	txrName(txrNm),
	useOwnSize(false),
	lockRotation(false)
{
	sf::Texture& txrRef = sl::GetPreLoader().GetTexture(txrNm);

	Start(txrRef, GetOriginFromTxr(txrRef.getSize()));
}

SpriteRenderer::SpriteRenderer(std::string txrNm, bool useOwnSize, bool lockRotation, sf::Vector2f origin)
	: Component(SPRITE_RENDERER),
	txrName(txrNm),
	useOwnSize(useOwnSize),
	lockRotation(lockRotation)
{
	sf::Texture& txrRef = sl::GetPreLoader().GetTexture(txrNm);
	if(origin.x == 0 && origin.y == 0) origin = GetOriginFromTxr(txrRef.getSize());
	Start(txrRef, origin);
}

void SpriteRenderer::Start(sf::Texture& txrRef, sf::Vector2f origin) // Sets the size and origin of the sprite
{
	sprite.setTexture(txrRef);
	sprite.setPosition(object.GetPos());
	sprite.setOrigin(origin);
	if (useOwnSize) object.SetSize((sf::Vector2f)txrRef.getSize());
	else { // If useOwnSize is false, get the set te scale of the sprite to fit the object
		sf::Vector2f scale;
		scale.x = object.GetSize().x / txrRef.getSize().x;
		scale.y = object.GetSize().y / txrRef.getSize().y;
		sprite.setScale(scale);
	}
}

void SpriteRenderer::Render(sf::RenderWindow& window)
{
	//move if position has changed
	if (sprite.getPosition().x != object.GetPos().x || sprite.getPosition().y != object.GetPos().y || sprite.getRotation() != object.GetRot())
	{
		sprite.setPosition(object.GetPos());
		if(!lockRotation) sprite.setRotation(object.GetRot());
	}
	window.draw(sprite);
}

sf::Vector2f SpriteRenderer::GetScale()
{
	return sprite.getScale();
}

sf::Vector2f SpriteRenderer::GetOrigin()
{
	return sprite.getOrigin();
}

void SpriteRenderer::SetOrigin(sf::Vector2f origin)
{
	sprite.setOrigin(origin);
}

void SpriteRenderer::SetOrigin(float x, float y)
{
	sprite.setOrigin(sf::Vector2f(x, y));
}

sf::Vector2f SpriteRenderer::GetOriginFromTxr(sf::Vector2u txrSize)
{
	return sf::Vector2f((float)(txrSize.x / 2), (float)(txrSize.y / 2));
}

bool SpriteRenderer::UseSizeCheck(sf::Vector2f& size)
{
	if (size.x == 1 && size.y == 1) {
		return true;
	}
	return false;
}

void SpriteRenderer::SetColor(sf::Color& col)
{
	sprite.setColor(col);
}

std::string SpriteRenderer::GetSaveData()
{
	std::string data;
	data += std::to_string(type) + " ";
	data += txrName + " "; //name of the texture
	data += std::to_string(useOwnSize) + " ";
	data += std::to_string(lockRotation) + " ";
	sf::Vector2f origin = sprite.getOrigin();
	sf::Vector2f txrSize = (sf::Vector2f)sl::GetPreLoader().GetTexture(txrName).getSize();
	if (useOwnSize && txrSize / 2.f == origin) origin = sf::Vector2f(0, 0);
	data += std::to_string(origin.x) + " ";
	data += std::to_string(origin.y) + " ";
	return data;
}
