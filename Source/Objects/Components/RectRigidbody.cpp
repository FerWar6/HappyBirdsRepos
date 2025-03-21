#include "RectRigidbody.h"
#include "Objects/Object.h"

// This constructor is used to create a RectBody from a position and size
RectRigidbody::RectRigidbody(b2Vec2 posInM, b2Vec2 sizeInM,
    b2BodyType type, float dens, b2WorldId& id)
    : Component(RECT_RIGIDBODY),
    density(dens)
{
    object.SetPosInM(posInM);
    object.SetSizeInM(sizeInM);
    Start(type, id);
}

// This constructor is used for creating a RectBody on top of an existing object. Used to construct from scene data
RectRigidbody::RectRigidbody(b2BodyType type, float dens, b2WorldId& id)
    : Component(RECT_RIGIDBODY),
    density(dens)
{
    Start(type, id);
}
void RectRigidbody::Start(b2BodyType type, b2WorldId& id)
{
    // Creates the RectBody
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.position = object.GetPosInM();
    bodyId = b2CreateBody(id, &defaultBody);

    b2Vec2 sizeInM = object.GetSizeInM();
    b2Polygon polygon = b2MakeBox(sizeInM.x / 2, sizeInM.y / 2);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.enableHitEvents = true;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
}

RectRigidbody::~RectRigidbody()
{
    b2DestroyBody(bodyId);
}

void RectRigidbody::FixedUpdate()
{
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);
    object.SetPosInM(pos);
    object.SetRot(std::atan2(rot.s, rot.c) * 180 / 3.14159f);
    //std::cout << "Box  ";
    //std::cout << "x: " << pos.x << "y: " << pos.y << "\n";
}

b2BodyType RectRigidbody::GetBodyType()
{
    return b2Body_GetType(bodyId);
}

std::string RectRigidbody::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(density) + " ";
    data += std::to_string(b2Body_GetType(bodyId)) + " ";
    return data;
}

