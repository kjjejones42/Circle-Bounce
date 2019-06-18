#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "CircleContainer.h"
#include "cScreen.h"
#include "Title.h"

// Helper function to translate boolean values to On/Off strings.
std::string boolToText(bool input);

// Screen for the Simulation game mode.
class screen1Simulation : public cScreen
{
	// Pointer to the global settings object/
	Settings* settings;
	// Container object for the bouncing circles.
	CircleContainer container;
	// Title object for the explanatory text that appears when the screen is first called.
	Title title;
	// Black background to the Title text.
	sf::RectangleShape rect;
	// Determines whether the screen is showing the Title, or if the simulation has begun.
	bool onTitleMessage = true;
public:
	screen1Simulation();
	// Main screen function loop.
	virtual int Run(sf::RenderWindow &window);
	// Resets the screen to the initial state.
	virtual void reset();
};