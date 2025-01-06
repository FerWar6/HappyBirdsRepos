#include "CannonBall.h"

CannonBall::CannonBall(b2Vec2 posInMeters)
    : Object()
{
    b2BodyDef defaultBody = b2DefaultBodyDef();
    defaultBody.type = b2_dynamicBody;  // Dynamic body for movement
    defaultBody.position = { posInMeters.x, posInMeters.y }; // Position in meters

    // Create the body in the world
    b2BodyId bodyId = b2CreateBody(manager->GetWorldId(), &defaultBody);

    // Step 2: Define the circle shape
    b2Circle circle;                           // Circle definition
    circle.radius = (float)5;            // Radius in meters

    // Step 3: Define the shape properties
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;       // Mass density (kg/m^2)
    shapeDef.friction = 0.3f;      // Friction coefficient
    shapeDef.restitution = 0.5f;   // Bounciness

    // Step 4: Attach the shape to the body
    b2CreateCircleShape(bodyId, &shapeDef, &circle);
}

b2BodyId CannonBall::GetBodyId()
{
	return bodyId;
}

void CannonBall::Render(sf::RenderWindow& window)
{
    std::cout << "rendering circle\n";
}
