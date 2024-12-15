#include "PhysicsObject.h"
#include <iostream>
PhysicsObject::PhysicsObject(b2Vec2 posInMeters, b2Vec2 sizeInMeters,
    b2BodyType type, float density)
    : Object(posInMeters, sizeInMeters)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.position = { posInMeters.x, posInMeters.y };
    bodyId = b2CreateBody(manager->GetWorldId(), &defaultBody);

    b2Polygon polygon = b2MakeBox(sizeInMeters.x, sizeInMeters.y);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
    //std::cout << "object pos: " << GetPos().x << " , " << GetPos().y << "\n";
    //std::cout << "object size: " << GetSize().x << " , " << GetSize().y << "\n";
}

b2BodyId PhysicsObject::GetBodyId()
{
	return bodyId;
}

void PhysicsObject::Update()
{
}

void PhysicsObject::FixedUpdate()
{
}

//void PhysicsObject::Render(sf::RenderWindow& window)
//{
//    b2Vec2 pos = b2Body_GetPosition(bodyId);
//    b2Rot rot = b2Body_GetRotation(bodyId);
//    sf::Vector2f size = GetSize();
//
//    float radians = std::atan2(rot.s, rot.c);
//    float degrees = -radians * 180 / 3.14159f;
//    sf::RectangleShape objVisual(sf::Vector2f(size.x * 50, size.y * 50));
//    objVisual.setOrigin(size.x/2, size.y/2);
//    int scale = manager->worldScale;
//
//    objVisual.setPosition(pos.x * scale, -pos.y * scale);
//    objVisual.setRotation(degrees);
//    objVisual.setFillColor(sf::Color::Red);
//    //std::cout << "rendering obj at: " << pos.x * scale << " , " << -pos.y * scale << "\n";
//    window.draw(objVisual);
//    //sf::RectangleShape test(sf::Vector2f(size.x * 50, size.y * 50));
//    //test.setOrigin(size.x / 2, size.y / 2);
//    //test.setPosition(pos.x * 50, pos.y * 50);
//    //window.draw(test);
//}
