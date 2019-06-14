#include "screen2Game.h"
#include "settings.h"
#include "font.h"

int screen2Game::Run(sf::RenderWindow &window)
{
	Settings* settings = Settings::getInstance();
	double randColor = settings->getRandom(0, 1);

	while (true)
	{
		window.clear(settings->hslToRgb(std::fmod(randColor += 0.001, 1.0), 1.0, 0.05));
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					return cScreen::EXIT_PROGRAM;

				case sf::Event::KeyReleased:
					return cScreen::SIMULATION;

				case sf::Event::Resized:
				{
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
					double diffX = (int)event.size.width - settings->previousWindowWidth;
					settings->previousWindowWidth = event.size.width;
					break;
				}
			}
		}
		window.display();
	}
	return cScreen::EXIT_PROGRAM;
}