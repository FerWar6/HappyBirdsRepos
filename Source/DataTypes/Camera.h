#pragma once
#include "SFML/Graphics/View.hpp"
struct Camera {
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
private:
	sf::Vector2f position;
};