#pragma once

#include "DataTypes/Vector2.h"
#include "DataTypes/Size.h"

struct Transform{
	Transform();
	Transform(Vector2 pos, float rotation, Size size);
	Vector2 position;
	float rotation;
	Size size;
};

