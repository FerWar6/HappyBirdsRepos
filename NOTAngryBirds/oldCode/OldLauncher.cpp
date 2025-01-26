//#include "OldLauncher.h"
//#include "Engine/PreLoader.h"
//#include "Engine/Engine.h"
//#include "Managers/InputManager.h"
//OldLauncher::OldLauncher()
//	: Object()
//{
//	
//	sf::Texture& standTxr = manager->preLoaderPtr->GetTexture("LauncherStand");
//	sf::Texture& launcherTxr = manager->preLoaderPtr->GetTexture("Launcher");
//	sf::Texture& ringTxr = manager->preLoaderPtr->GetTexture("LauncherRing");
//	sf::Texture& previewDotTxr = manager->preLoaderPtr->GetTexture("PreviewDot");
//	standSprite.setTexture(standTxr);
//	launcherSprite.setTexture(launcherTxr);
//	ringSprite.setTexture(ringTxr);
//	previewDotSprite.setTexture(previewDotTxr);
//
//	sf::Vector2f pos(300, 500);
//	standSprite.setPosition(pos);
//	launcherSprite.setPosition(pos);
//	ringSprite.setPosition(launcherSprite.getPosition());
//
//	sf::Vector2f scale(1.5,1.5);
//	standSprite.setScale(scale);
//	launcherSprite.setScale(scale);
//
//	standSprite.setOrigin(sf::Vector2f(25, 6));
//	launcherSprite.setOrigin(sf::Vector2f(13, 87));
//	ringSprite.setOrigin(ringTxr.getSize().x/2, ringTxr.getSize().y / 2);
//	previewDotSprite.setOrigin(previewDotTxr.getSize().x/2, previewDotTxr.getSize().y / 2);
//}
//
//void OldLauncher::Update()
//{
//}
//
//void OldLauncher::FixedUpdate()
//{
//
//}
//
//void OldLauncher::Render(sf::RenderWindow& window)
//{
//
//	launcherSprite.setRotation(GetLauncherAngle() + 90);
//	window.draw(launcherSprite);
//	window.draw(standSprite);
//	ringSprite.setScale(sf::Vector2f(.75,.75));
//	window.draw(ringSprite);
//	ringSprite.setScale(sf::Vector2f(2, 2));
//	window.draw(ringSprite);
//
//	sf::Vector2i mousePos = manager->enginePtr->GetInputManager().mousePos;
//
//	sf::Vertex line[] =
//	{
//		sf::Vertex(launcherSprite.getPosition()),
//		sf::Vertex((sf::Vector2f)mousePos)
//	};
//
//	window.draw(line, 2, sf::Lines);
//	DrawPreview(window);
//}
//
//sf::Vector2f OldLauncher::GetLaunchPoint()
//{
//	sf::Vector2 launcherPos(launcherSprite.getPosition());
//	float offset = 0;
//	float radians = (GetLauncherAngle() + offset) / 180 * 3.14159f;
//	sf::Vector2f pos;
//	float distance = 130;
//	pos.x = distance * cos(radians) + launcherPos.x;
//	pos.y = distance * sin(radians) + launcherPos.y;
//	return pos;
//}
//
//float OldLauncher::GetLauncherAngle()
//{
//	sf::Vector2i mousePos = manager->enginePtr->GetInputManager().mousePos;
//	sf::Vector2 launcherPos(launcherSprite.getPosition());
//	float angle = atan2(launcherPos.y - mousePos.y, launcherPos.x - mousePos.x);
//	angle = angle * 180 / 3.14159f;
//	return angle;
//}
//
//float OldLauncher::GetLaunchVelocity()
//{
//	sf::Vector2i mousePos = manager->enginePtr->GetInputManager().mousePos;
//	sf::Vector2f launchPoint(launcherSprite.getPosition());
//	float distance = sqrt(pow(launchPoint.x - mousePos.x, 2) + pow(launchPoint.y - mousePos.y, 2) * 1.0);
//	float maxDistance = 125;
//	float minVelocity = 5;
//	float maxVelocity = 15;
//	float velocity = std::clamp(distance - 85, (float)0, maxDistance);
//	velocity = velocity / maxDistance * (maxVelocity - minVelocity) + minVelocity;
//	return velocity;
//}
//
//b2Vec2 OldLauncher::GetLaunchMomentum()
//{
//	b2Vec2 launchMomentum;
//	float distance = GetLaunchVelocity();
//	float radians = GetLauncherAngle() / 180 * 3.14159f;
//	sf::Vector2f launchPoint = GetLaunchPoint();
//	launchMomentum.x = distance * cos(radians);
//	launchMomentum.y = distance * sin(radians);
//	//std::cout << "x: " << launchMomentum.x << " y: " << launchMomentum.y << "\n";
//	//std::cout << "GetLaunchDistance: " << distance << "\n";
//	return launchMomentum;
//}
//
//float OldLauncher::GetXWidth(float angle, float velocity, int amountOfDots, float arcLenght)
//{
//	float g = 9.8f;
//	float newArchLenght;
//
//
//	double low = 0.0, high = 100.0;
//	double tolerance = 0.00000000001;
//
//	while (high - low > tolerance) {
//		double mid = (low + high) / 2.0;
//		double length = GetArchLength(mid, angle, velocity);
//
//		if (fabs(length - arcLenght) < tolerance)
//			return mid;
//		else if (length < arcLenght)
//			low = mid;
//		else
//			high = mid;
//	}
//	float returnValue = (low + high) / 2.0 / amountOfDots;
//	//std::cout << "returnValue : " << (returnValue > 2 ? returnValue : 2) << "\n";
//	//std::cout << "retrunValue: " << returnValue << "\n";
//	return returnValue;
//	//return returnValue > 2 ? returnValue : 2;
//}
//
//void OldLauncher::DrawPreview(sf::RenderWindow& window)
//{
//	//y = h + x * tan(angle) - g * (x^2) / (2 * V0^2 * cos^2(angle))
//	
//	//input needs to be the distance between dots
//	//find the x using the distance between dots
//	//
//	float startDistanceMultiplier = 1;
//	int amountOfDots = 15;
//	float archLenght = 10;
//
//	for (int i = 0; i < amountOfDots; i++) {
//		float g = 9.8f;
//		float angle = GetLauncherAngle() / 180 * 3.14159f;
//		float velocity = GetLaunchVelocity() * 3.14159f;
//		bool flipPreview = !(angle < 3.14159f / 2 && angle > -3.14159f / 2);
//		if (flipPreview) angle = angle - (angle - 3.14159f/2) * 2;
//		//float x = i * 7;
//		float x = (startDistanceMultiplier + i) * GetXWidth(angle, velocity, amountOfDots, archLenght);
//		float y = (x * tan(angle) + (g * std::pow(x, 2)) / (2 * std::pow(velocity, 2) * std::pow(cos(angle), 2)));
//		sf::Vector2f launchPos(GetLaunchPoint());
//		float scale = 5;
//		previewDotSprite.setPosition(flipPreview ? launchPos.x + -x * scale : launchPos.x + x * scale, launchPos.y + y * scale);
//		sf::Color c(255,255,255, 255 - 255 / amountOfDots * i);
//		previewDotSprite.setColor(c);
//		window.draw(previewDotSprite);
//		//std::cout << "GetXWidth: " << GetXWidth(angle, velocity, amountOfDots, archLenght) << "\n";
//
//		//std::cout << "angle: " << angle << "\n";
//	}
//}
//
//double OldLauncher::GetArchLength(double x, float angle, float velocity)
//{
//	float g = 9.8f;
//	int n = 100; // Number of intervals for integration
//	double h = x / n; // Step size
//	double sum = 0.0;
//
//	for (int i = 0; i <= n; ++i) {
//		double xi = i * h;
//		double f = sqrt(1 + pow(tan(angle) + (g * xi) / (velocity * velocity * pow(cos(angle), 2)), 2));
//		if (i == 0 || i == n)
//			sum += f;
//		else if (i % 2 == 0)
//			sum += 2 * f;
//		else
//			sum += 4 * f;
//	}
//
//	return (h / 3.0) * sum; // Simpson's Rule for numerical integration
//}
