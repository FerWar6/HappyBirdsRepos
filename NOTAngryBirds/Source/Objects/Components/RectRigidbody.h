#pragma once
#include "Objects/Components/Component.h"
#include "box2d/box2d.h"

struct RectRigidbody : public Component
{
	RectRigidbody(b2Vec2 posInMeters, b2Vec2 sizeInMeters,
		b2BodyType type, float density, b2WorldId& id);
	RectRigidbody(b2BodyType type, float density, b2WorldId& id);
	void FixedUpdate() override;
	b2BodyId bodyId;

	float density;
	b2BodyType GetBodyType();

	std::string GetSaveData() override;
};
