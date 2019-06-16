#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "settings.h"

// This class implements a written message that sits in the centre of the screen. Add messages to add a new line.
class Title : public sf::Drawable
{
	// Container of the individual lines of text that make up the message.
	std::vector<sf::Text> textArray;

	// Pointer to the global settings object
	Settings *settings;

	// The number of pixels between each line, including the line height itself.
	const int lineSpacing = 40;

public:
	Title() : settings(Settings::getInstance())
	{
	}
	// Draw method extended from the SFML library
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < (int)textArray.size(); i++)
		{
			target.draw(textArray[i], states);
		}
	}

	// Function that adds a message to the title
	Title& addMessage(std::string string);

	// Moves each line of text to the centre of the screen, offset to place each line below another
	void recalculatePosition();

	// Moves the entire title on the screen
	void move(double x, double y);
};
