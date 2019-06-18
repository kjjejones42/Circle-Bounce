#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"

// Class that handles the update messages that appear whenever the player changes settings.
class Message : public sf::Drawable
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1, 1> >;

	// SFML Text object for the message text.
	sf::Text text;
	// Black rectangle for the text background.
	sf::RectangleShape textBackground;
	// Pointer to the global settings object.
	Settings *settings;
	// Integer out of 100 that determines the Message opacity. 
	int opacity;	
	// Timer variables to help determine how long the message should stay on screen.
	std::chrono::time_point<clock_t> messageTimer;
	std::chrono::duration<int> messageDuration;
	// Determines if the Message should remain unchanged or begin to fade.
	bool expired = true;

public:
	Message();
	// SFML function to draw Message to screen.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(textBackground, states);
		target.draw(text, states);
	}
	// Resizes the background rectangle to fit the Message text.
	void recalcBackgroundSize();
	// Sets the text of the Message, sets opacity to 100%, and starts the timer.
	void setMessage(std::string message);
	// Change the Message opacity to a given value out of 100.
	void setOpacity(int opacity);
	// Updates the message each time is called. Mainly used to allow the Message to fade.
	void update();	
};