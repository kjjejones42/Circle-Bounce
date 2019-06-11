#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "CircleContainer.h"
#include "cScreen.h"

std::string boolToText(bool input);

class screen0Simulation : public cScreen
{
public:
	screen0Simulation(void) {};
	virtual int Run(sf::RenderWindow &window);
};