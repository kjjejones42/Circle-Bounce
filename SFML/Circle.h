#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include "settings.h"

class CircleContainer;

class Circle : public sf::CircleShape
{
	Settings *settings ;
	sf::Vector2f momentum;
	bool loading;
	double loadProgress;
	CircleContainer* const parent;
	void init(CircleContainer* const c_parent);

public:
	Circle();
	Circle(CircleContainer* const c_parent);
	void updateOpacity();
	bool isInValidArea();
	void setRandomPosition();
	void resize();
	void update();
	void resizedWindow(bool windowResize);
};