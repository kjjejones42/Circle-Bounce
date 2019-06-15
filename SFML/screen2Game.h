#pragma once
#include "cScreen.h"
class screen2Game : public cScreen
{
	int score;
public:
	screen2Game() : score(0) {};
	virtual int Run(sf::RenderWindow &window);
};

