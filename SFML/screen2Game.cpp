#include "screen2Game.h"

screen2Game::screen2Game() : 
	settings(Settings::getInstance()),
	randColor(settings->getRandom(0, 1)),
	player(Player()),
	mouse(sf::CircleShape()),
	container(CircleContainer(1)),
	goal(Goal()),
	title(Title()),
	rect(sf::RectangleShape()),
	onTitleMessage(true)
{
	mouse.setRadius(3);
	title.addMessage("GAME CONTROLS")
		.addMessage("Get the red circle!")
		.addMessage("Move using the mouse.")
		.addMessage("Avoid every other circle.")
		.addMessage("\n")
		.addMessage("Press any key to start.")
		.addMessage("Press Esc to pause, and press Esc again to return to the start screen.");
	rect.setFillColor(sf::Color(0, 0, 0, 255 * 0.8));
}

void screen2Game::reset()
{
	goal.setRandomPosition();
	container.reset();
	container.addCircles(1);
};

int screen2Game::Run(sf::RenderWindow &window)
{
	window.setMouseCursorVisible(false);
	while (true)
	{
		rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		window.clear(settings->hslToRgb(std::fmod(randColor += 0.001, 1.0), 1.0, 0.05));
		sf::Event event;

		if (onTitleMessage)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::KeyReleased:
					{
						if (event.key.code == sf::Keyboard::Escape)
						{
							reset();
							return cScreen::START;
						}
						onTitleMessage = false;
						break;
					}						

					case sf::Event::Closed:
						return cScreen::EXIT_PROGRAM;

					case sf::Event::Resized:
					{
						title.recalculatePosition();
						window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
						break;
					}
				}
			}
			title.recalculatePosition();
			window.draw(container);
			window.draw(goal);
			window.draw(player);
			window.draw(rect);
			window.draw(title);
		}
		else
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Escape)
					{
						onTitleMessage = true;
						break;
					}

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
				default:
					break;
				}
			}
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			player.setSeekPoint(mousePosition);
			mouse.setPosition(mousePosition.x, mousePosition.y);
			player.update();
			container.update();

			if (container.checkCollision(player))
			{
				return cScreen::GAME_OVER;
			}
			if (goal.checkCollision(player))
			{
				cScreen::score++;
				container.addCircles(1);
				container.message.setMessage("Score: " + std::to_string(score));
				goal.setRandomPosition();
			}
			window.draw(container);
			window.draw(goal);
			window.draw(player);
			window.draw(mouse);
		}
		window.display();
	}
	
	return cScreen::EXIT_PROGRAM;
}