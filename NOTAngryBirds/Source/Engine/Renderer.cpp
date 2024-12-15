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
    //b2WorldDef worldDef = b2DefaultWorldDef();
    //worldDef.gravity = { 0.0f, -9.81f };
    //worldId = b2CreateWorld(&worldDef);

    //b2BodyDef groundDef = b2DefaultBodyDef();
    //groundDef.position = { 0.0f, -5.0f }; // Adjusted closer to visible range
    //groundId = b2CreateBody(worldId, &groundDef);

    //b2Polygon groundBox = b2MakeBox(8.0f, 0.5f); // Width 8m, Height 0.5m
    //b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    //b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    //// Create first dynamic cube
    //b2BodyDef cubeDef1 = b2DefaultBodyDef();
    //cubeDef1.type = b2_dynamicBody;
    //cubeDef1.position = { 0.55f, 10.0f }; // Initial position of the first cube
    //cubeId1 = b2CreateBody(worldId, &cubeDef1);

    //b2Polygon cubeBox1 = b2MakeBox(0.5f, 0.5f); // Cube size 0.5m x 0.5m
    //b2ShapeDef cubeShapeDef1 = b2DefaultShapeDef();
    //cubeShapeDef1.density = 1.0f;
    //b2CreatePolygonShape(cubeId1, &cubeShapeDef1, &cubeBox1);

    // Create second dynamic cube (falls on top of the first cube)
    //b2BodyDef cubeDef2 = b2DefaultBodyDef();
    //cubeDef2.type = b2_dynamicBody;
    //cubeDef2.position = { 0.0f, 15.0f }; // Initial position of the second cube (above the first one)
    //cubeId2 = b2CreateBody(worldId, &cubeDef2);

    //b2Polygon cubeBox2 = b2MakeBox(0.5f, 0.5f); // Cube size 0.5m x 0.5m
    //b2ShapeDef cubeShapeDef2 = b2DefaultShapeDef();
    //cubeShapeDef2.density = 1.0f;
    //b2CreatePolygonShape(cubeId2, &cubeShapeDef2, &cubeBox2);
}
void Renderer::Render()
{
    window.clear();
    objectsToRender = manager->GetObjects();
    for (auto& obj : objectsToRender) {
        obj->Render(window);
    }
    //const float fixedTimeStep = 1.0f / 6000.0f;
    //b2World_Step(worldId, fixedTimeStep, 8);

    //b2Vec2 groundPos = b2Body_GetPosition(groundId);
    //sf::RectangleShape groundRect(sf::Vector2f(800.0f, 50.0f)); // Adjusted for pixels
    //groundRect.setOrigin(400.0f, 25.0f);
    //groundRect.setPosition(400.0f + (groundPos.x * scale), 600 - (groundPos.y * scale));
    //groundRect.setFillColor(sf::Color::Green);
    //window.draw(groundRect);

    //// Render second cube
    //b2Vec2 cubePos2 = b2Body_GetPosition(cubeId2);
    //b2Rot cubeRotation2 = b2Body_GetRotation(cubeId2); // Get the rotation as b2Rot
    //float cubeAngle2 = std::atan2(cubeRotation2.s, cubeRotation2.c); // Convert to angle in radians
    //sf::RectangleShape cubeRect2(sf::Vector2f(50.0f, 50.0f)); // Adjusted for pixels
    //cubeRect2.setOrigin(25.0f, 25.0f);
    //cubeRect2.setPosition(400.0f + (cubePos2.x * scale), 600 - (cubePos2.y * scale)); // Render using its position
    //cubeRect2.setRotation(-cubeAngle2 * 180.0f / 3.14159f); // Convert radians to degrees
    //cubeRect2.setFillColor(sf::Color::Blue);
    //window.draw(cubeRect2);

    //std::cout << "rendering obj at: " << cubePos2.x * scale << " , " << -cubePos2.y * scale << "\n";
    window.display();
}