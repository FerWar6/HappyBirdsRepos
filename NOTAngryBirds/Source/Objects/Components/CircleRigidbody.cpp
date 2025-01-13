#include "CircleRigidbody.h"
#include "Objects/Object.h"
#include "Managers/GameManager.h"

CircleRigidbody::CircleRigidbody(b2Vec2 posInM, float radiusInM,
    b2BodyType type, b2WorldId& id, float dens)
    : Component(ComponentType::CIRCLE_RIGIDBODY),
    density(dens)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.position = posInM;
    bodyId = b2CreateBody(id, &defaultBody);

    // build circle body
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = dens;

    b2Circle circleData = { b2Vec2{0,0}, radiusInM };
    b2CreateCircleShape(bodyId, &shapeDef, &circleData);

    object->SetSizeInM(b2Vec2{ radiusInM * 2, radiusInM * 2 });
}

CircleRigidbody::CircleRigidbody(b2Vec2 posInM, float radiusInM, b2Vec2 startVel, b2WorldId& id, float dens)
    : Component(ComponentType::CIRCLE_RIGIDBODY),
    density(dens)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = b2_dynamicBody;
    defaultBody.position = posInM;
    defaultBody.linearVelocity = startVel;
    bodyId = b2CreateBody(id, &defaultBody);

    // build circle body
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = dens;

    b2Circle circleData = { b2Vec2{0,0}, radiusInM };
    b2CreateCircleShape(bodyId, &shapeDef, &circleData);

    object->SetSizeInM(b2Vec2{ radiusInM * 2, radiusInM * 2 });
}

CircleRigidbody::CircleRigidbody(b2BodyType type, float dens, b2WorldId& id)
    : Component(ComponentType::CIRCLE_RIGIDBODY),
    density(dens)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = b2_dynamicBody;
    defaultBody.position = object->GetPosInM();
    bodyId = b2CreateBody(id, &defaultBody);

    // build circle body
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = dens;

    b2Circle circleData = { b2Vec2{0,0}, object->GetSize().x};
    b2CreateCircleShape(bodyId, &shapeDef, &circleData);
}

void CircleRigidbody::FixedUpdate()
{
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);
    object->SetPosInM(pos);
    object->SetRot(std::atan2(rot.s, rot.c) * 180 / 3.14159f);
}

b2BodyType CircleRigidbody::GetBodyType()
{
    return b2Body_GetType(bodyId);
}

//void CircleRigidbody::Render(sf::RenderWindow& window)
//{
//    int scale = object.manager->worldScale;
//    b2Vec2 pos = b2Body_GetPosition(bodyId);
//    b2Rot rot = b2Body_GetRotation(bodyId);
//
//    float radians = std::atan2(rot.s, rot.c);
//    float degrees = radians * 180 / 3.14159f;
//
//    sf::CircleShape objVisual(object.GetSize().x / 2);
//    objVisual.setOrigin(object.GetSize().x / 2, object.GetSize().y / 2);
//
//    objVisual.setPosition(pos.x * scale, pos.y * scale);
//    objVisual.setRotation(degrees);
//    objVisual.setFillColor(sf::Color::Green);
//    window.draw(objVisual);
//}
