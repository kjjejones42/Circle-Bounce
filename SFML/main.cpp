#pragma once

#include "main.h"
#include "cScreen.h"
#include "screen0Start.h"
#include "screen1Simulation.h"

int main()
{
	std::vector<cScreen*> Screens;
	Screens.resize(cScreen::NUM_OF_SCREENS);

	screen0Start s0;
	Screens[cScreen::START] = &s0;

	screen1Simulation s1;
	Screens[cScreen::SIMULATION] = &s1;
		
	Settings* settings = Settings::getInstance();
	int screen = settings->initialScreen;

	sf::ContextSettings windowSettings;
	sf::RenderWindow window(sf::VideoMode(settings->window.x, settings->window.y), "Circle Bounce", sf::Style::Default, windowSettings);
	window.setVerticalSyncEnabled(settings->vSync);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}

	return EXIT_SUCCESS;
}