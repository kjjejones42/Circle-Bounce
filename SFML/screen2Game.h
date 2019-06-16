#pragma once
#include "cScreen.h"
#include "settings.h"
#include "player.h"
#include "CircleContainer.h"
#include "Goal.h"
#include "Title.h"

class screen2Game : public cScreen
{
	Player player;
	sf::CircleShape mouse;
	Settings* settings;
	CircleContainer container;
	double randColor;
	Goal goal;
	Title title;
	sf::RectangleShape rect;
	bool onTitleMessage = true;

public:
	screen2Game();
	virtual int Run(sf::RenderWindow &window);
	virtual void reset();
};

