#include "Transform.h"

Transform::Transform()
	: Component("Transform")
{
	position.x = 0;
	position.y = 0;
	rotation.c = 0;
	rotation.s = 0;
	scale.w = 1;
	scale.h = 1;
}

void Transform::ComponentBehaviour()
{
}
