#pragma once

#include "SFML/Graphics.hpp"

// Class to act as the various program screens. Can be extended to add individual behaviours.
class cScreen
{
public:
	// Static variable to keep track of the player's Game score. Allows score to be communicated between Game and Game Over screens.
	static int score;
	// Use this function to activate the screen, passing in the window where the screen should be drawn
	virtual int Run(sf::RenderWindow &App) = 0;
	// This function should restore the screen to the initialisation state.
	virtual void reset() {};
	// Enumeration that keeps track of the screens, total number of screens, and the program exit code.
	enum screenName {
		EXIT_PROGRAM = -1,
		SIMULATION,
		START,
		GAME,
		GAME_OVER,
		NUM_OF_SCREENS
	};
};

