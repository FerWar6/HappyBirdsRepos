#pragma once
#include "box2d/box2d.h"
#include "Objects/Object.h"
class PhysicsObject : public Object
{
public:
	PhysicsObject(b2Vec2 posInMeters, b2Vec2 sizeInMeters, 
	b2BodyType type, float density);
	b2BodyId GetBodyId();
private:
	b2BodyId bodyId;
	virtual void Update();
	virtual void FixedUpdate();
	//virtual void Update() override;
	//virtual void FixedUpdate() override;
	//virtual void Render(sf::RenderWindow& window) override;
};


