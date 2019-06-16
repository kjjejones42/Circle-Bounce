#pragma once

#include "cScreen.h"
#include "screen0Start.h"
#include "settings.h"
#include "Title.h"

class screen3GameOver : public cScreen
{
	Settings *settings;
public:
	screen3GameOver() : settings(Settings::getInstance()) {};
	int Run(sf::RenderWindow &window);
	virtual void reset();
};

