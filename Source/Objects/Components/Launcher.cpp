#include "Launcher.h"
#include "Managers/InputManager.h"
#include "Managers/ServiceLocator.h"
#include "Objects/Components/CircleRigidbody.h"
#include "Objects/Components/SpriteRenderer.h"
#include "Engine/Engine.h"
#include "Engine/PreLoader.h"
#include <cmath>
#include <iostream>
Launcher::Launcher(std::string txrNm, int numOfAmmo)
    : Component(LAUNCHER),
    inputMan(sl::GetInputManager()),
    primed(false),
    ammoCount(numOfAmmo)
{
    sf::Texture& txrRef = sl::GetPreLoader().GetTexture(txrNm);
    dotSprite.setTexture(txrRef);
    dotSprite.setOrigin(txrRef.getSize().x / 2, txrRef.getSize().y / 2);
    buttonMinRadius = 120;
    buttonMaxRadius = 500;
    minVelocity = 5;
    maxVelocity = 15;
    amountOfDots = 15;
    minAngle = -70;
    maxAngle = 10;
    moveSpeed = 1;
}

void Launcher::Update()
{
    //holding click primes the cannon
    //when primed you can move the cannon back to the center and unprime it
    //when primed you can move it back as far as you want and release to shoot the cannonball

    //if (inputMan.GetKeyDown(MOUSE_L)) primed = true;
    //if (inputMan.GetKeyDown(MOUSE_R)) primed = false;
    //if (inputMan.GetKeyUp(MOUSE_L)) SpawnProjectile();


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
    //dont update unless the angle is valid
    if (primed) {
        object.SetRot(CalcAngle() + spriteRotationalOffset);
        UpdatePreview();
    }
    else {
        MoveBackToBasePos();
    }
    //std::cout << "Angle: " << CalcAngle() << "\n";

}

void Launcher::Render(sf::RenderWindow& window)
{
    if (primed) {
        {
            sf::CircleShape circle;
            float radius = buttonMaxRadius;
            circle.setRadius(radius);
            circle.setOrigin(radius, radius);
            circle.setPosition(object.GetPos());
            sf::Color col(255, 255, 255, 25);
            circle.setFillColor(col);
            window.draw(circle);
        } 
        {
            sf::CircleShape circle;
            float radius = 10;
            circle.setRadius(radius);
            circle.setOrigin(radius, radius);
            circle.setPosition(CalcLaunchPoint());
            sf::Color col(255, 255, 255, 50);
            circle.setFillColor(col);
            window.draw(circle);
        }
        {
            sf::CircleShape circle;
            float radius = buttonMinRadius;
            circle.setRadius(radius);
            circle.setOrigin(radius, radius);
            circle.setPosition(object.GetPos());
            sf::Color col(255, 0, 0, 100);
            circle.setFillColor(col);
            window.draw(circle);
        }

    }
    if(primed && (HoveringOver(buttonMinRadius)) ) DrawPreview(window);
}

std::string Launcher::GetSaveData()
{
    return std::string();
}
void Launcher::SpawnProjectile()
{
    ammoCount--;
    if (primed && (HoveringOver(buttonMinRadius))) {
        int scale = sl::GetEngine().worldScale;
        b2Vec2 spawnPos = b2Vec2{ CalcLaunchPoint().x / scale, CalcLaunchPoint().y / scale };
        Object* obj = new Object();
        float ballSize = 0.5f;
        obj->AddComponent<CircleRigidbody>(spawnPos, ballSize, CalcLinearVelocity(), sl::GetWorldId());
        obj->AddComponent<SpriteRenderer>("CannonBall");
        primed = false;
        //std::cout << "created projectile \n";
    }
    else {
        primed = false;
    }
}

bool Launcher::HoveringOver(float min, float max)
{
    //return true when in between the range of the button radius
    if (max == 0) return CalcDistanceToMouse() > min;
    return CalcDistanceToMouse() > min && CalcDistanceToMouse() < max;
}

float Launcher::CalcAngle()
{
    //calculates the angle from object to mouse
    sf::Vector2i mousePos = inputMan.GetMousePos();
    sf::Vector2 launcherPos(object.GetPos());
    float angle = atan2(mousePos.y - launcherPos.y, mousePos.x - launcherPos.x);
    //float angle = atan2(launcherPos.y - mousePos.y, launcherPos.x - mousePos.x);
    angle = angle * 180 / 3.14159f;
    return std::clamp(angle, minAngle, maxAngle);
}

bool Launcher::IsAngleValid()
{
    float angle = CalcAngle();
    return angle == minAngle || angle == maxAngle;
}

float Launcher::CalcDistanceToMouse()
{
    //calculates distance from object to mouse
    sf::Vector2i mousePos = inputMan.GetMousePos();
    sf::Vector2f launchPoint(object.GetPos());
    return sqrt(pow(launchPoint.x - mousePos.x, 2) + pow(launchPoint.y - mousePos.y, 2) * 1.0);
}

float Launcher::CalcInvalidAngleDistance()
{
    bool useWidth = inputMan.GetMousePos().y < object.GetPos().y;
    if (useWidth) return inputMan.GetMousePos().x - object.GetPos().x;
    return object.GetPos().y - inputMan.GetMousePos().y;
}

float Launcher::CalcVelocity()
{
    //calculates velocity based on the distance from object to mouse and maps that to a velocity
    float distance = CalcDistanceToMouse();
    float velocity = std::clamp(distance - buttonMinRadius, (float)0, buttonMaxRadius - buttonMinRadius);
    velocity = velocity / (buttonMaxRadius - buttonMinRadius) * (maxVelocity - minVelocity) + minVelocity;
    return velocity;
}

b2Vec2 Launcher::CalcLinearVelocity()
{
    //calculates the linear velocity an object would get if launched at a specific angle and velocity
    //used to shoot the cannonball
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

sf::Vector2f Launcher::CalcLaunchPoint()
{
    //calculates the tip of the cannon where the cannon ball is shot from and preview is drawn from
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

void Launcher::UpdatePreview()
{
    float startDistanceMultiplier = 1;
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

void Launcher::DrawPreview(sf::RenderWindow& window)
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
	//return returnValue > 2 ? returnValue : 2;
}

double Launcher::GetArchLength(double x, float angle, float velocity)
{
    float g = 9.8f;
    int n = 100; // Number of intervals for integration
    double h = x / n; // Step size
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

    return (h / 3.0) * sum; // Simpson's Rule for numerical integration
}
