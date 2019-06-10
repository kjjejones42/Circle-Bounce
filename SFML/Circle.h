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
	CircleContainer* parent;

public:		
	Circle(CircleContainer* c_parent = nullptr);
	void updateOpacity();
	bool isInValidArea();
	void setRandomPosition();
	void resize();
	void update();
	void resizedWindow(bool windowResize);
};