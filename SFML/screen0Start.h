#pragma once

#include "cScreen.h"
#include "settings.h"
#include "Title.h"

// Screen that implements the initial Start screen
class screen0Start : public cScreen
{
public:
	screen0Start() {};
	// Main screen function loop.
	virtual int Run(sf::RenderWindow &window);
	// Resets screen to initial values.
	virtual void reset();
};

