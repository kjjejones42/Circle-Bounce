#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"
#include "Player.h"

// The Goal circle that the Player must collide with.
class Goal : public sf::CircleShape
{
	// Pointer to the global settings object.
	Settings* settings;
	// Diameter of the goal circle in pixels.
	int diameter;

public:
	Goal();
	// Moves the Goal to a random position on the screen.
	void setRandomPosition();
	// Determines whether the goal is currently colliding with the Player.
	bool checkCollision(Player &player);
};

