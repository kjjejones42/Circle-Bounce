#pragma once
#include "cScreen.h"
#include "settings.h"
#include "player.h"
#include "CircleContainer.h"
#include "Goal.h"
#include <iostream>

class screen2Game : public cScreen
{
	Player player;
	sf::CircleShape mouse;
	Settings* settings;
	CircleContainer container;
	double randColor;
	Goal goal;

public:
	screen2Game();
	virtual int Run(sf::RenderWindow &window);
	virtual void reset();
};

