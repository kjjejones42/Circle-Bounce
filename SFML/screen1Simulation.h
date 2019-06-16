#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "CircleContainer.h"
#include "cScreen.h"
#include "Title.h"

std::string boolToText(bool input);

class screen1Simulation : public cScreen
{
	Settings* settings;
	CircleContainer container;
	Title title;
	sf::RectangleShape rect;
	bool onTitleMessage = true;
public:
	screen1Simulation();
	virtual int Run(sf::RenderWindow &window);
	virtual void reset();
};