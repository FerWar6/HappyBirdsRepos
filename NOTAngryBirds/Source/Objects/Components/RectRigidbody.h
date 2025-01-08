#pragma once
#include "Objects/Components/Component.h"
#include "box2d/box2d.h"

class RectRigidbody : public Component
{
public:
	RectRigidbody(Object& obj, b2Vec2 posInMeters, b2Vec2 sizeInMeters,
		b2BodyType type, float density, b2WorldId& id);

	void FixedUpdate() override;
	b2BodyId bodyId;

};
