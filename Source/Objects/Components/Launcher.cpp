#include "Launcher.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Engine/Engine.h"
#include "Engine/PreLoader.h"
#include <cmath>
#include <iostream>
Launcher::Launcher(int numOfAmmo)
    : Component(LAUNCHER),
    inputMan(sl::GetInputManager()),
    primed(false),
    ammoCount(numOfAmmo),
    maxAmmo(numOfAmmo)
{
    sf::Texture& txrRef = sl::GetPreLoader().GetTexture("PreviewDot"); //set the sprite of the dots
    dotSprite.setTexture(txrRef);
    dotSprite.setOrigin(txrRef.getSize().x / 2, txrRef.getSize().y / 2);
    minRadius = 120;
    maxRadius = 500;
    minVelocity = 5;
    maxVelocity = 15;
    amountOfDots = 15;
    minAngle = -70;
    maxAngle = 10;
    moveSpeed = 1;
}

void Launcher::Update()
{
    if (!active) return; // Turns off cannon functionality inside of edit mode
    //holding click primes the cannon
    //when primed you can move the cannon back to the center and unprime it
    //when primed you can move it back as far as you want and release to shoot the cannonball

    if (ammoCount > 0) {
        if (inputMan.GetKeyDown(MOUSE_L)) {
            primed = true;
        }
        if (inputMan.GetKeyDown(MOUSE_R)) {
            primed = false;
        }
        if (inputMan.GetKeyUp(MOUSE_L)) {
            SpawnProjectile();
        }
    }
}

void Launcher::FixedUpdate() 
{
    if (!active) return; // Turns off cannon functionality inside of edit mode
    if (primed) { // Updates preview when primed
        object.SetRot(CalcAngle() + spriteRotationalOffset);
        UpdatePreview();
    }
    else {
        MoveBackToBasePos(); // moves back cannon when not primed
    }
    //std::cout << "Angle: " << CalcAngle() << "\n";
}

void Launcher::Render(sf::RenderWindow& window)
{
    //if (primed) { // Shows circles for the min and max cannon range
    //    sf::CircleShape circle;
    //    circle.setOrigin(10, 10);

    //    circle.setRadius(maxRadius);
    //    circle.setPosition(object.GetPos());
    //    circle.setFillColor(sf::Color(255, 255, 255, 25));
    //    window.draw(circle);

    //    circle.setRadius(10);
    //    circle.setPosition(CalcLaunchPoint());
    //    circle.setFillColor(sf::Color(255, 255, 255, 50));
    //    window.draw(circle);

    //    circle.setRadius(minRadius);
    //    circle.setPosition(object.GetPos());
    //    circle.setFillColor(sf::Color(255, 0, 0, 100));
    //    window.draw(circle);
    //}
    if(primed && (HoveringOver(minRadius)) ) DrawPreview(window); // Draws preview when primed
}

std::string Launcher::GetSaveData()
{
    std::string data;
    data += std::to_string(type) + " ";
    data += std::to_string(maxAmmo) + " ";
    return data;
}

void Launcher::SpawnProjectile() 
{
    if (primed && (HoveringOver(minRadius))) { // Spawns cannonball when primed and releasing mouse
        int scale = sl::GetEngine().worldScale;
        float ballSize = 1;
        float ballDensity = 2;
        Object* obj = new Object(CalcLaunchPoint(), 0 , sf::Vector2f(ballSize * scale, ballSize * scale));
        CircleRigidbody* body = obj->AddComponent<CircleRigidbody>(b2_dynamicBody, ballDensity, sl::GetWorldId());
        body->SetVelocity(CalcLinearVelocity());
        obj->AddComponent<SpriteRenderer>("CannonBall");
        primed = false;
        ammoCount--;
        if (ammoCount == 0) sl::GetEngine().GetGameManager().SetLastShotTaken(true);
    }
    else {
        primed = false;
    }
}

bool Launcher::HoveringOver(float min, float max)
{
    //return true if the distance to the mouse is bigger than the minDistance
    if (max == 0) return CalcDistanceToMouse() > min;
    return CalcDistanceToMouse() > min && CalcDistanceToMouse() < max;
}

float Launcher::CalcAngle() // Calculates the angle from object to mouse
{
    sf::Vector2i mousePos = inputMan.GetMousePos();
    sf::Vector2 launcherPos(object.GetPos());
    float angle = atan2(mousePos.y - launcherPos.y, mousePos.x - launcherPos.x);
    angle = angle * 180 / 3.14159f;
    return std::clamp(angle, minAngle, maxAngle);
}

bool Launcher::IsAngleValid() // returns if the angle is between minAngle and maxAngle
{
    float angle = CalcAngle();
    return angle == minAngle || angle == maxAngle;
}

float Launcher::CalcDistanceToMouse() // Calculates the distance between the mouse and cannon
{
    sf::Vector2i mousePos = inputMan.GetMousePos();
    sf::Vector2f launchPoint(object.GetPos());
    return sqrt(pow(launchPoint.x - mousePos.x, 2) + pow(launchPoint.y - mousePos.y, 2) * 1.0);
}

float Launcher::CalcInvalidAngleDistance() // Calculates what velocity to use when angle is invalid
{
    bool useWidth = inputMan.GetMousePos().y < object.GetPos().y;
    if (useWidth) return inputMan.GetMousePos().x - object.GetPos().x;
    return object.GetPos().y - inputMan.GetMousePos().y;
}

float Launcher::CalcVelocity() // Calculates velocity based on the distance from object to mouse and maps that to a velocity
{
    float distance = CalcDistanceToMouse();
    float velocity = std::clamp(distance - minRadius, (float)0, maxRadius - minRadius);
    velocity = velocity / (maxRadius - minRadius) * (maxVelocity - minVelocity) + minVelocity;
    return velocity;
}

b2Vec2 Launcher::CalcLinearVelocity() // Calculates the linear velocity an object would get if launched at a specific angle and velocity
{
    b2Vec2 launchMomentum;
    float distance = CalcVelocity();
    float radians = CalcAngle() / 180 * 3.14159f;
    sf::Vector2f launchPoint = CalcLaunchPoint();
    launchMomentum.x = distance * cos(radians);
    launchMomentum.y = distance * sin(radians);
    //std::cout << "x: " << launchMomentum.x << " y: " << launchMomentum.y << "\n";
    //std::cout << "GetLaunchDistance: " << distance << "\n";
    return launchMomentum;
}

sf::Vector2f Launcher::CalcLaunchPoint() // Calculates the tip of the cannon where the cannon ball is shot from and preview is drawn from
{
    sf::Vector2 launcherPos(object.GetPos());
    float angle = CalcAngle() / 180 * 3.14159f;
    sf::Vector2f pos;
    float distance = 130;
    pos.x = distance * cos(angle) + launcherPos.x;
    pos.y = distance * sin(angle) + launcherPos.y;
    return pos;
}

void Launcher::MoveBackToBasePos()
{
    float targetRot = spriteRotationalOffset;
    float angle = object.GetRot();
    if (angle > targetRot) {
        angle -= moveSpeed;
        object.SetRot(angle < targetRot ? targetRot : angle);
    }
    else {
        angle += moveSpeed;
        object.SetRot(angle > targetRot ? targetRot : angle);
    }
}

void Launcher::UpdatePreview() // Updates the dotpositions / preview
{
    float startDistanceMultiplier = .5;
    float archLenght = 10;
    //y = h + x * tan(angle) - g * (x^2) / (2 * V0^2 * cos^2(angle))

    bool createVector = dotPositions.size() == 0;
    for (int i = 0; i < amountOfDots; i++) {
        float g = 9.8f;
        float angle = CalcAngle() / 180 * 3.14159f;
        float velocity = CalcVelocity() * 3.14159f;
        bool flipPreview = !(angle < 3.14159f / 2 && angle > -3.14159f / 2);
        if (flipPreview) angle = angle - (angle - 3.14159f / 2) * 2;
        float x = (startDistanceMultiplier + i) * GetXWidth(angle, velocity, amountOfDots, archLenght);
        float y = (x * tan(angle) + (g * std::pow(x, 2)) / (2 * std::pow(velocity, 2) * std::pow(cos(angle), 2)));
        sf::Vector2f launchPos(CalcLaunchPoint());
        float scale = 5;
        if (createVector) {
            dotPositions.push_back(sf::Vector2f(flipPreview ? launchPos.x + -x * scale : launchPos.x + x * scale, launchPos.y + y * scale));
        }
        else {
            dotPositions[i] = sf::Vector2f(flipPreview ? launchPos.x + -x * scale : launchPos.x + x * scale, launchPos.y + y * scale);
        }
        //std::cout << "GetXWidth: " << GetXWidth(angle, velocity, amountOfDots, archLenght) << "\n";
        //std::cout << "angle: " << angle << "\n";
    }
}

void Launcher::SetPreview(float angle, float velocity, sf::Vector2f previewPos)
{
    //y = h + x * tan(angle) - g * (x^2) / (2 * V0^2 * cos^2(angle))
    float startDistanceMultiplier = 1;
    float archLenght = 10;

    bool createVector = dotPositions.size() == 0;
    for (int i = 0; i < amountOfDots; i++) {
        float g = 9.8f;
        bool flipPreview = !(angle < 3.14159f / 2 && angle > -3.14159f / 2);
        if (flipPreview) angle = angle - (angle - 3.14159f / 2) * 2;
        float x = (startDistanceMultiplier + i) * GetXWidth(angle, velocity, amountOfDots, archLenght);
        float y = (x * tan(angle) + (g * std::pow(x, 2)) / (2 * std::pow(velocity, 2) * std::pow(cos(angle), 2)));
        float scale = 5;
        if (createVector) {
            dotPositions.push_back(sf::Vector2f(flipPreview ? previewPos.x + -x * scale : previewPos.x + x * scale, previewPos.y + y * scale));
        }
        else {
            dotPositions[i] = sf::Vector2f(flipPreview ? previewPos.x + -x * scale : previewPos.x + x * scale, previewPos.y + y * scale);
        }
    }
}

void Launcher::DrawPreview(sf::RenderWindow& window) // Draws dots at all points in dotPositions
{
    int i = 0;
    for (auto dot : dotPositions) { 
        float scale = 5;
        dotSprite.setPosition(dot);
        auto index = std::find(dotPositions.begin(), dotPositions.end(), dot);
        sf::Color c(255, 255, 255, 255 - 255 / amountOfDots * i);
        dotSprite.setColor(c);
        window.draw(dotSprite);
        i++;
    }
}

float Launcher::GetXWidth(float angle, float velocity, int amountOfDots, float arcLenght)
{
    float g = 9.8f;
	float newArchLenght;

	double low = 0.0, high = 100.0;
	double tolerance = 0.00000000001;

	while (high - low > tolerance) {
		double mid = (low + high) / 2.0;
		double length = GetArchLength(mid, angle, velocity);

		if (fabs(length - arcLenght) < tolerance)
			return mid;
		else if (length < arcLenght)
			low = mid;
		else
			high = mid;
	}
	float returnValue = (low + high) / 2.0 / amountOfDots;
	//std::cout << "returnValue : " << (returnValue > 2 ? returnValue : 2) << "\n";
	//std::cout << "retrunValue: " << returnValue << "\n";
	return returnValue;
}

double Launcher::GetArchLength(double x, float angle, float velocity) // Get arch length using numerical intergration
{
    float g = 9.8f;
    int n = 100;
    double h = x / n; 
    double sum = 0.0;

    for (int i = 0; i <= n; ++i) {
        double xi = i * h;
        double f = sqrt(1 + pow(tan(angle) + (g * xi) / (velocity * velocity * pow(cos(angle), 2)), 2));
        if (i == 0 || i == n)
            sum += f;
        else if (i % 2 == 0)
            sum += 2 * f;
        else
            sum += 4 * f;
    }

    return (h / 3.0) * sum;
}
