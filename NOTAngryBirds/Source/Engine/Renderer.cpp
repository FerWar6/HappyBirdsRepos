#include "Renderer.h"
#include "Managers/ServiceLocator.h"
Renderer::Renderer(sf::RenderWindow& win)
    : manager(sl::GetGameManager()),
    window(win)
{
    worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, -9.8f };
    worldId = b2CreateWorld(&worldDef);
    groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = { 0.0f, 0.0f };
    groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);

    groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { 0.0f, 4.0f };
    bodyId = b2CreateBody(worldId, &bodyDef);

    dynamicBox = b2MakeBox(1.0f, 1.0f);

    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;

    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void Renderer::Render()
{
    window.clear();
    objectsToRender = manager->GetObjects();
    for (auto& obj : objectsToRender) {
        obj->Render(window);
    }

    sf::RectangleShape shape;
    sf::Vector2f pos = sf::Vector2f(groundBodyDef.position.x, groundBodyDef.position.y);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    b2World_Step(worldId, timeStep, subStepCount);
    b2Vec2 position = b2Body_GetPosition(bodyId);
    b2Rot rotation = b2Body_GetRotation(bodyId);
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
    b2DebugDraw::DrawPolygon(dynamicBox.vertices, 4, b2_colorAliceBlue, dynamicBox);
    shape.setPosition(pos);
    window.display();
}