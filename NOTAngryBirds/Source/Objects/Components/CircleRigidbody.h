#pragma once
#include "Objects/Components/Component.h"
#include "box2d/box2d.h"
class CircleRigidbody : public Component
{
public:
	CircleRigidbody(Object& obj, b2Vec2 posInMeters, float radiusInMeters,
		b2BodyType type, b2WorldId& id, float density = 1);

	CircleRigidbody(Object& obj, b2Vec2 posInMeters, float radiusInMeters,
		b2Vec2 startingMomentum, b2WorldId& id, float density = 1);

	void FixedUpdate() override;
	b2BodyId bodyId;
};
