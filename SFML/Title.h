#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "settings.h"

class Title : public sf::Drawable
{
	std::vector<sf::Text> textArray;
	sf::RectangleShape textBackground;
	Settings *settings;

public:
	Title() : settings(Settings::getInstance())
	{
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(textBackground, states);
		for (int i = 0; i < textArray.size(); i++)
		{
			target.draw(textArray[i], states);
		}
	}
	Title& addMessage(std::string string);
	void calculateVerticalPosition();
	void move(double x, double y);
};
