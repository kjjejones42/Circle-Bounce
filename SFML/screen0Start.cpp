#include "screen0Start.h"

class Title
{
};

int screen0Start::Run(sf::RenderWindow &window)
{
	while (true)
	{
		window.clear(sf::Color::Black);
		sf::Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				case sf::Event::Closed:
					return cScreen::EXIT;

				case sf::Event::KeyReleased:
					return cScreen::SIMULATION;
			}
		}

		window.display();
	}
	return cScreen::EXIT;
}