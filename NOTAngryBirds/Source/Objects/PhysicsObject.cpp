#include "PhysicsObject.h"
#include <iostream>
PhysicsObject::PhysicsObject(b2Vec2 posInMeters, b2Vec2 sizeInMeters,
    b2BodyType type, float density)
    : Object()
{
    SpriteRenderer* spriteRen = new SpriteRenderer();
    AddComponent(spriteRen);

    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.position = { posInMeters.x, posInMeters.y };
    bodyId = b2CreateBody(manager->GetWorldId(), &defaultBody);

    b2Polygon polygon = b2MakeBox(sizeInMeters.x / 2, sizeInMeters.y / 2);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
}

b2BodyId PhysicsObject::GetBodyId()
{
	return bodyId;
}

void PhysicsObject::Render(sf::RenderWindow& window)
{
    int scale = manager->worldScale;
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);
    sf::Vector2f size(.5, .5);
    size = sf::Vector2f(size.x * scale, size.y * scale);

    float radians = std::atan2(rot.s, rot.c);
    float degrees = radians * 180 / 3.14159f;
    sf::RectangleShape objVisual(size);
    objVisual.setOrigin(size.x / 2, size.y / 2);

    objVisual.setPosition(pos.x * scale, pos.y * scale);
    objVisual.setRotation(degrees);
    objVisual.setFillColor(sf::Color::Red);
    //std::cout << "rendering obj at: " << pos.x * scale << " , " << -pos.y * scale << "\n";
    window.draw(objVisual);
}
