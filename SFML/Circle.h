#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include "settings.h"

// Declaration of the CircleContainer class so the program compiles.
// As Circle and CircleContainer are mutually dependent it's difficult to simply include the CircleContainer header.
class CircleContainer;

// Class that implements the circles that bounce around the screen.
class Circle : public sf::CircleShape
{
	// Pointer to the global settings object.
	Settings *settings ;
	// Keeps track of the Circle's momentum in the X and Y directions.
	sf::Vector2f momentum;
	// Determines if the Circle has reached its full size and opacity or not.
	bool loading;
	// Min 0; Max 1. How far the Cirlce is to reaching its full size and opacity.
	double loadProgress;
	// Pointer to the container object.
	CircleContainer* const parent;
	// Setup function, can be called from constructor.
	void init();

public:
	Circle();
	Circle(CircleContainer* const c_parent);
	// Updates the Circle's opacity to suit how loaded it is.
	void updateOpacity();
	// Checks whether the Circle has collided with screen borders or not.
	bool isInValidArea();
	// Moves the circle to a random position on the screen.
	void setRandomPosition();
	// Updates the Circle's size to match the container's diameter variable.
	void resize();
	// Moves the Circle according to its momentum and position.
	void update();
	// Updates the Circle's position when the window is resized. 
	void resizedWindow(bool windowResize);
};