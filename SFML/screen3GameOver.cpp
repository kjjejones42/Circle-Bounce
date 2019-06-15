#include "screen3GameOver.h"
#include "settings.h"
#include "font.h"
#include "Title.h"

int screen3GameOver::Run(sf::RenderWindow &window)
{
	Settings* settings = Settings::getInstance();
	double randColor = settings->getRandom(0, 1);
	Title title;
	title.addMessage("GAME OVER!")
		.addMessage("\n")
		.addMessage("Your score was:")
		.addMessage(std::to_string(cScreen::score))
		.addMessage("\n")
		.addMessage("Press any key to return to the Start screen.");

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
			{
				cScreen::score = 0;
				return cScreen::START;
			}

			case sf::Event::Resized:
			{
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
				double diffX = (int)event.size.width - settings->previousWindowWidth;
				settings->previousWindowWidth = event.size.width;
				title.move(diffX / 2.0, 0.0);
				title.calculateVerticalPosition();
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