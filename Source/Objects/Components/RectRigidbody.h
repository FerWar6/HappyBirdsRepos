#pragma once
#include "Objects/Components/Component.h"
#include "box2d/box2d.h"

class RectRigidbody : public Component
{
public:
	RectRigidbody(b2BodyType type, float density, b2WorldId& id);
	~RectRigidbody() override;
	void FixedUpdate() override;
	b2BodyId bodyId;

	float density;
	b2BodyType GetBodyType();

	std::string GetSaveData() override;
private:
	void Start(b2BodyType type, b2WorldId& id);
};
