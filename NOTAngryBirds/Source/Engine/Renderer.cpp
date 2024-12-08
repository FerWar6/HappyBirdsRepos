#include "Renderer.h"
#include "Managers/ServiceLocator.h"
#include <cmath>
#define PI 3.14159265358979323846

Renderer::Renderer(sf::RenderWindow& win)
    : manager(sl::GetGameManager()),
    window(win)
{}

void Renderer::Start()
{
    float windowHalf = window.getSize().x / 2;
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, -9.8f };
    worldId = b2CreateWorld(&worldDef);
    

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = { windowHalf, -500 };
    groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(groundSize.x, groundSize.y);

    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef1 = b2DefaultBodyDef();
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position = { windowHalf, 0 };

    bodyDef1.rotation = { -0.799335, 0.600886 };
    bodyId1 = b2CreateBody(worldId, &bodyDef1);

    b2Polygon dynamicBox1 = b2MakeSquare(boxSize1);
    b2ShapeDef shapeDef1 = b2DefaultShapeDef();
    shapeDef1.density = 1.0f;
    shapeDef1.friction = 0.3f;

    b2CreatePolygonShape(bodyId1, &shapeDef1, &dynamicBox1);


    b2BodyDef bodyDef2 = b2DefaultBodyDef();
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position = { windowHalf -45, -100 };
    bodyDef2.rotation = { -0.799335, 0.600886 };
    bodyId2 = b2CreateBody(worldId, &bodyDef2);

    b2Polygon dynamicBox2 = b2MakeSquare(boxSize2);

    b2ShapeDef shapeDef2 = b2DefaultShapeDef();
    shapeDef2.density = 1.0f;
    shapeDef2.friction = 0.3f;

    b2CreatePolygonShape(bodyId2, &shapeDef2, &dynamicBox2);
}
void Renderer::Render()
{
    window.clear();
    //objectsToRender = manager->GetObjects();
    //for (auto& obj : objectsToRender) {
    //    obj->Render(window);
    //}
    float windowHalf = window.getSize().x / 2;
    float timeStep = 1.0f / 1000;
    int subStepCount = 5;
    double angleRadians;
    double angleDegrees;
    b2World_Step(worldId, timeStep, subStepCount);

    b2Vec2 position = b2Body_GetPosition(groundId);
    b2Rot rotation = b2Body_GetRotation(groundId);

    sf::RectangleShape groundShape;
    sf::Vector2f groundPos = sf::Vector2f(position.x, -position.y);

    groundShape.setPosition(groundPos);
    groundShape.setSize(groundSize);
    groundShape.setOrigin(groundSize.x / 2, 0);
    groundShape.setFillColor(sf::Color::Green);
    window.draw(groundShape);

    position = b2Body_GetPosition(bodyId1);
    rotation = b2Body_GetRotation(bodyId1);
    
    angleRadians = std::atan2(rotation.c, rotation.s);
    angleDegrees = angleRadians * (180.0 / PI);

    sf::RectangleShape shape1;
    sf::Vector2f shape1Pos = sf::Vector2f(position.x, -position.y);

    float testMiltiplier = 2.5f;
    shape1.setPosition(shape1Pos);
    shape1.setRotation(angleDegrees);
    shape1.setOrigin(boxSize1 / 2, boxSize1 / 2);
    shape1.setSize(sf::Vector2f(boxSize1 * testMiltiplier, boxSize1 * testMiltiplier));
    shape1.setFillColor(sf::Color::Red);
    window.draw(shape1);

    position = b2Body_GetPosition(bodyId2);
    rotation = b2Body_GetRotation(bodyId2);

    sf::RectangleShape shape2;
    sf::Vector2f shape2Pos = sf::Vector2f(position.x, -position.y);

    angleRadians = std::atan2(rotation.c, rotation.s);
    angleDegrees = angleRadians * (180.0 / PI);

    shape2.setPosition(shape2Pos);
    shape2.setRotation(angleDegrees);
    shape2.setOrigin(boxSize2/2, boxSize2 / 2);
    shape2.setSize(sf::Vector2f(boxSize2 * testMiltiplier, boxSize2 * testMiltiplier));
    shape2.setFillColor(sf::Color::Blue);
    window.draw(shape2);
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(5,5), sf::Color::Red),
        sf::Vertex(sf::Vector2f(50,50), sf::Color::Red)
    };
    window.draw(shape1);
    window.draw(line, 2, sf::Lines);
    //std::cout << "x pos: " << position.x << " y pos: " << position.y << std::endl;
    window.display();
}