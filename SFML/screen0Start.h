#pragma once

#include "cScreen.h"
#include "settings.h"
#include "Title.h"

class screen0Start : public cScreen
{
public:
	screen0Start() {};
	virtual int Run(sf::RenderWindow &window);
	virtual void reset();
};

