#pragma once

#include "main.h"
#include "cScreen.h"
#include "screen0Start.h"
#include "screen1Simulation.h"

int main()
{
	Settings* settings = Settings::getInstance();
		
	sf::ContextSettings windowSettings;
	sf::RenderWindow window(
		sf::VideoMode(settings->initialWindowWidth, settings->initialWindowHeight),
		"Circle Bounce",
		sf::Style::Default,
		windowSettings);
	window.setVerticalSyncEnabled(settings->vSync);
	settings->window = &window;

	std::vector<cScreen*> Screens(cScreen::NUM_OF_SCREENS);
	screen0Start s0;
	Screens[cScreen::START] = &s0;
	screen1Simulation s1;
	Screens[cScreen::SIMULATION] = &s1;

	int screen = settings->initialScreen;
	while (screen != cScreen::EXIT_PROGRAM)
	{
		screen = Screens[screen]->Run(window);
	}

	return EXIT_SUCCESS;
}