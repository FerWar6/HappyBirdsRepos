#pragma once
#include "Objects/Components/Component.h"
#include "box2d/box2d.h"

class RectRigidbody : public Component
{
public:
	RectRigidbody(b2BodyType type, float density, b2WorldId& id);
	~RectRigidbody() override;
	void FixedUpdate() override;

	float density;
	b2BodyId& GetBodyId();
	b2BodyType GetBodyType();

	std::string GetSaveData() override;
private:
	b2BodyId bodyId;
	void Start(b2BodyType type, b2WorldId& id);
};
