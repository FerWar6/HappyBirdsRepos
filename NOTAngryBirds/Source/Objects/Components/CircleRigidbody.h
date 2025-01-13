#pragma once
#include "Objects/Components/Component.h"
#include "box2d/box2d.h"
struct CircleRigidbody : public Component
{
	CircleRigidbody(b2Vec2 posInMeters, float radiusInMeters,
		b2BodyType type, b2WorldId& id, float density = 1);

	CircleRigidbody(b2Vec2 posInMeters, float radiusInMeters,
		b2Vec2 startingMomentum, b2WorldId& id, float density = 1);

	CircleRigidbody(b2BodyType type, float density, b2WorldId& id);

	void FixedUpdate() override;
	b2BodyId bodyId;


	float density;
	b2BodyType GetBodyType();
};
