#pragma once
#include "box2d/box2d.h"
#include "Objects/Object.h"
#include "Components/SpriteRenderer.h"
class PhysicsObject : public Object
{
public:
	PhysicsObject(b2Vec2 posInMeters, b2Vec2 sizeInMeters,
		b2BodyType type = b2_dynamicBody, float density = 1);
	b2BodyId GetBodyId();
private:
	b2BodyId bodyId;
	virtual void Render(sf::RenderWindow& window) override;
};


