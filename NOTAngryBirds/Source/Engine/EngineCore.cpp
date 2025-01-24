#include "EngineCore.h"
#include <iostream>
#include <stdio.h>
#include "wtypes.h"

EngineCore::EngineCore()
	: engine(),
	renderer(window, engine.objects)
{
	//dont quite understand this yet, but it puts the console in a more visible place
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 1000, 1000, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	sf::Vector2i screenSize(desktop.right, desktop.bottom);
	int widthMargin = 200;
	int heightMargin = 150;
	winWidth = screenSize.x - widthMargin * 2;
	winHeight = screenSize.y - heightMargin * 2;

	winWidth = 1500;
	winHeight = 900;

	windowName = "Happy Birds";
	window.create(sf::VideoMode(winWidth, winHeight), windowName);
	engine.GetManager()->SetWindow(&window);
	window.setPosition(sf::Vector2i(widthMargin, heightMargin));
	//window.setPosition(sf::Vector2i(700,300));
	//window.setPosition(sf::Vector2i(200,65));

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 9.8f };
    worldId = b2CreateWorld(&worldDef);
	engine.GetManager()->SetWorldId(&worldId);
	
	engine.Start();
	renderer.Start();
	Start();
}

void EngineCore::Start()
{
	LoopEngine();
}

void EngineCore::LoopEngine()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closed engine" << std::endl;
				window.close();
			}
		}
		engine.UpdateObjectsVector();

		sf::Time elapsed = gameClock.restart();
		accumulator += elapsed.asSeconds();

		//TO-DO: check for any updates in gameobjects
		while (accumulator >= timeStep) {
			//std::cout << accumulator << "\n";
			engine.FixedUpdate();
            b2World_Step(worldId, timeStep, 4);
            accumulator -= timeStep;
		}
		engine.Update();
		renderer.Render();
	}
}