#pragma once
#include "cScreen.h"
#include "settings.h"
#include "player.h"
#include "CircleContainer.h"
#include "Goal.h"
#include "Title.h"

// Screen that implements the Game program mode.
class screen2Game : public cScreen
{
	// The arrowhead player object.
	Player player;
	// The small circle that represents the mouse pointer.
	sf::CircleShape mouse;
	// Pointer to the global settings object/
	Settings* settings;
	// Container object for the bouncing circles.
	CircleContainer container;
	// The hue variable for the background colour.
	double randColor;
	// The red circle that the player needs to reach.
	Goal goal;
	// The explanatory text that appears when the screen is first called.
	Title title;
	// Black background to the title text.
	sf::RectangleShape rect;
	// Sets whether to show the title or not.
	bool onTitleMessage = true;

public:
	screen2Game();
	// Main game function loop.
	virtual int Run(sf::RenderWindow &window);
	// Resets the screen to initial settings.
	virtual void reset();
};

