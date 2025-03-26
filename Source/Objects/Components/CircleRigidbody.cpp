#include "CircleRigidbody.h"
#include "Objects/Object.h"

CircleRigidbody::CircleRigidbody(b2BodyType type, float dens, b2WorldId& id)
    : Component(CIRCLE_RIGIDBODY),
    density(dens)
{
    Start(type, id);
}

CircleRigidbody::~CircleRigidbody()
{
    b2DestroyBody(bodyId); // Destroy body when destroying CircleRidigbody
}

void CircleRigidbody::Start(b2BodyType type, b2WorldId& id) // Build the circle body
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.isEnabled = true;
    defaultBody.position = object.GetPosInM();
    bodyId = b2CreateBody(id, &defaultBody);
    
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.enableHitEvents = true;
    b2Circle circleData = { b2Vec2{0,0}, object.GetSizeInM().x / 2 };
    b2CreateCircleShape(bodyId, &shapeDef, &circleData);
}

void CircleRigidbody::FixedUpdate()
{
    if (!active) return;
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);
    object.SetPosInM(pos);
    object.SetRot(std::atan2(rot.s, rot.c) * 180 / 3.14159f); // From sine and cosine to radians to degrees
}

void CircleRigidbody::SetVelocity(b2Vec2 vel)
{
    b2Body_SetLinearVelocity(bodyId, vel);
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