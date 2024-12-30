#pragma once
#include "Components/Component.h"

struct Vector2 {
	float x, y;
};
struct Rotation {
	float c, s;
};
struct Scale {
	float w, h;
};
struct Transform : Component{
	Transform();
	void ComponentBehaviour() override;
	Vector2 position;
	Rotation rotation;
	Scale scale;
};