#pragma once
#include "SFML/Graphics/View.hpp"
#include <iostream>
class Camera {
public:
	Camera() 
	{
		zoomLevels[0] = .5;
		zoomLevels[1] = .75;
		zoomLevels[2] = 1;
		zoomLevels[3] = 1.5;
		zoomLevels[4] = 2;
		currentZoomIndex = 2;
	};
	sf::View view;
	void SetView(sf::RenderWindow& win) {
		view = win.getDefaultView();
	}
	sf::View& GetView() {
		return view;
	}
	void SetPos(sf::Vector2f pos) {
		sf::Vector2f newPos = pos - position;
		view.move(newPos);
		position = pos;
		//std::cout << "x: " << position.x << " y:" << position.y << "\n";
	}
	void SetPos(float x, float y) {
		sf::Vector2f pos(x, y);
		sf::Vector2f newPos = pos - position;
		view.move(newPos);
		position = pos;
		//std::cout << "x: " << position.x << " y: " << position.y << "\n";
	}
	sf::Vector2f GetPos() {
		return position;
	}
	void IncreaseZoom() {
		if (currentZoomIndex - 1 > 0) {
			view.zoom(zoomLevels[currentZoomIndex - 1] / zoomLevels[currentZoomIndex]);
			currentZoomIndex--;
			//std::cout << "zoom in\n";
		}
	}
	void DecreaseZoom() {
		if (currentZoomIndex + 1 < 5) {	// amount of elements in zoomlevels is 5
			view.zoom(zoomLevels[currentZoomIndex + 1] / zoomLevels[currentZoomIndex]);
			currentZoomIndex++;
			//std::cout << "zoom out\n";
		}
	}
private:
	sf::Vector2f position;
	float zoomLevels[5];
	int currentZoomIndex;
};