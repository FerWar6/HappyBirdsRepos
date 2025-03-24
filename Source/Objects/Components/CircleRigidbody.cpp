#include "CircleRigidbody.h"
#include "Objects/Object.h"

CircleRigidbody::CircleRigidbody(b2Vec2 posInM, float radiusInM, b2Vec2 startVel, b2WorldId& id, float dens)
    : Component(CIRCLE_RIGIDBODY),
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

    object.SetSizeInM(b2Vec2{ radiusInM * 2, radiusInM * 2 });
}

CircleRigidbody::CircleRigidbody(b2BodyType type, float dens, b2WorldId& id)
    : Component(CIRCLE_RIGIDBODY),
    density(dens)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = b2_dynamicBody;
    defaultBody.position = object.GetPosInM();
    bodyId = b2CreateBody(id, &defaultBody);

    // build circle body
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = dens;

    b2Circle circleData = { b2Vec2{0,0}, object.GetSize().x};
    b2CreateCircleShape(bodyId, &shapeDef, &circleData);
}

CircleRigidbody::~CircleRigidbody()
{
    b2DestroyBody(bodyId);
}

void CircleRigidbody::FixedUpdate()
{
    if (!active) return;
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);
    object.SetPosInM(pos);
    object.SetRot(std::atan2(rot.s, rot.c) * 180 / 3.14159f);
}

b2BodyId& CircleRigidbody::GetBodyId()
{
    return bodyId;
}

b2BodyType CircleRigidbody::GetBodyType()
{
    return b2Body_GetType(bodyId);
}

std::string CircleRigidbody::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(density) + " ";
    data += std::to_string(b2Body_GetType(bodyId)) + " ";
    return data;
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
