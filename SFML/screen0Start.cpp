#include "screen0Start.h"
#include "settings.h"
#include "font.h"
#include "Title.h"

void screen0Start::reset() {};

int screen0Start::Run(sf::RenderWindow &window)
{
	Settings* settings = Settings::getInstance();
	double randColor = settings->getRandom(0, 1);
	Title title;
	title.addMessage("Welcome to Circle Bounce!")
		.addMessage("\n")
		.addMessage("Press 'G' to start the game.")
		.addMessage("Press 'S' to start simulation mode.")
		.addMessage("Press Esc to exit.")
		.addMessage("\n")
		.addMessage("Or don't do anything, I'm not a cop.");

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
					switch (event.key.code)
					{
					case sf::Keyboard::S:
						return cScreen::SIMULATION;

					case sf::Keyboard::G:
						return cScreen::GAME;

					case sf::Keyboard::Escape:
						return cScreen::EXIT_PROGRAM;

					default:
						break;
					}
					break;

				case sf::Event::Resized:
				{
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
					double diffX = (int)event.size.width - settings->previousWindowWidth;
					settings->previousWindowWidth = event.size.width;
					title.move(diffX / 2.0, 0.0);
					title.recalculatePosition();
					break;
				}
				default:
					break;
			}
		}
		window.draw(title);
		window.display();
	}
	return cScreen::EXIT_PROGRAM;
}