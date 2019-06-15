#pragma once

#include "SFML/Graphics.hpp"

class cScreen
{
public:
	static int score;
	virtual int Run(sf::RenderWindow &App) = 0;
	enum screenName {
		EXIT_PROGRAM = -1,
		SIMULATION,
		START,
		GAME,
		GAME_OVER,
		NUM_OF_SCREENS
	};
};

