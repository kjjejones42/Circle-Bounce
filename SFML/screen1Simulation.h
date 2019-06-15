#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "CircleContainer.h"
#include "cScreen.h"

std::string boolToText(bool input);

class screen1Simulation : public cScreen
{
	Settings* settings;
	CircleContainer container;
public:
	screen1Simulation();
	virtual int Run(sf::RenderWindow &window);
	virtual void reset();
};