#pragma once
#include "Objects/Components/Component.h"
#include <box2d/box2d.h>
class CircleRigidbody : public Component
{
public:
	CircleRigidbody(b2BodyType type, float density, b2WorldId& id);
	~CircleRigidbody();

	void FixedUpdate() override;
	void SetVelocity(b2Vec2 vel); // Sets velocity of the body

	b2BodyId& GetBodyId();
	b2BodyType GetBodyType();

	std::string GetSaveData() override;
private:
	void Start(b2BodyType type, b2WorldId& id);
	b2BodyId bodyId;
	float density;
};
