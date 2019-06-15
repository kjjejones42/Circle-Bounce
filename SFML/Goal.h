#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"
#include "Player.h"

class Goal : public sf::CircleShape
{
	Settings* settings;
	int diameter;

public:
	Goal();
	void setRandomPosition();
	bool checkCollision(Player &player);
};

