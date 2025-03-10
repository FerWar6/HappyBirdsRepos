#include "RectRigidbody.h"
#include "Objects/Object.h"

RectRigidbody::RectRigidbody(b2Vec2 posInM, b2Vec2 sizeInM,
    b2BodyType type, float dens, b2WorldId& id)
    : Component(ComponentType::RECT_RIGIDBODY),
    density(dens)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.position = posInM;
    bodyId = b2CreateBody(id, &defaultBody);

    b2Polygon polygon = b2MakeBox(sizeInM.x / 2, sizeInM.y / 2);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = dens;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);

    object->SetPosInM(posInM);
    object->SetSizeInM(sizeInM);
}

RectRigidbody::RectRigidbody(b2BodyType type, float dens, b2WorldId& id)
    : Component(ComponentType::RECT_RIGIDBODY),
    density(dens)
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = type;
    defaultBody.position = object->GetPosInM();
    bodyId = b2CreateBody(id, &defaultBody);

    b2Vec2 sizeInM = object->GetSizeInM();
    b2Polygon polygon = b2MakeBox(sizeInM.x / 2, sizeInM.y / 2);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = dens;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);

    object->SetSizeInM(sizeInM);
}

void RectRigidbody::FixedUpdate()
{
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    b2Rot rot = b2Body_GetRotation(bodyId);
    object->SetPosInM(pos);
    object->SetRot(std::atan2(rot.s, rot.c) * 180 / 3.14159f);
    //std::cout << "Box  ";
    //std::cout << "x: " << pos.x << "y: " << pos.y << "\n";
}

b2BodyType RectRigidbody::GetBodyType()
{
    return b2Body_GetType(bodyId);
}

std::string RectRigidbody::GetSaveData()
{
    return std::string();
}
