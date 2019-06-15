#include "screen2Game.h"
#include "settings.h"
#include "player.h"
#include "CircleContainer.h"
#include <iostream>

int screen2Game::Run(sf::RenderWindow &window)
{
	window.setMouseCursorVisible(false);
	Settings* settings = Settings::getInstance();
	double randColor = settings->getRandom(0, 1);

	Player player;
	sf::CircleShape mouse;
	CircleContainer container(0);
	mouse.setRadius(3);
		
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

				case sf::Event::Resized:
				{
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
					float diffX = ((int)event.size.width - settings->previousWindowWidth) / 2;
					float diffY = ((int)event.size.height - settings->previousWindowHeight) / 2;
					settings->previousWindowWidth = event.size.width;
					settings->previousWindowHeight = event.size.height;
					player.move(diffX, diffY);
					break;
				}
			}
		}
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		player.setSeekPoint(mousePosition);
		mouse.setPosition(mousePosition.x, mousePosition.y);
		player.update();
		window.draw(container);
		window.draw(player);
		window.draw(mouse);
		window.display();
	}
	return cScreen::EXIT_PROGRAM;
}