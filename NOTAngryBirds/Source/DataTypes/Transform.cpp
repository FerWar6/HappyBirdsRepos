#include "Transform.h"

Transform::Transform()
	: position(),
	rotation(),
	size()
{
}

Transform::Transform(Vector2 pos, float rot, Size siz)
	: position(pos),
	rotation(rot),
	size(siz)
{
}