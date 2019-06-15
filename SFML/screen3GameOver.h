#pragma once
#include "cScreen.h"
#include "screen0Start.h"
#include "settings.h"

class screen3GameOver : public screen0Start
{
	Settings *settings;
public:
	screen3GameOver() : settings(Settings::getInstance()) {};
	int Run(sf::RenderWindow &window);
};

