#pragma once

#include "cScreen.h"
#include "screen0Start.h"
#include "settings.h"
#include "Title.h"

// The game over screen, to be called in Game screen if the player fails.
class screen3GameOver : public cScreen
{
	// Pointer to global settings object.
	Settings *settings;
public:
	screen3GameOver() : settings(Settings::getInstance()) {};
	// Use this function to activate the screen, passing in the window where the screen should be drawn
	int Run(sf::RenderWindow &App);
	// This function should restore the screen to the initialisation state.
	void reset();
};

