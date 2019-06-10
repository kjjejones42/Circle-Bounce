#pragma once

#include "main.h"

int main()
{	
	Message* message = Message::getInstance();
	Settings* settings = Settings::getInstance();
	CircleContainer container = CircleContainer(settings->minNumObjects);

	sf::ContextSettings windowSettings;
	sf::RenderWindow window(sf::VideoMode(settings->window.x, settings->window.y), "Circle Bounce", sf::Style::Default, windowSettings);
	window.setVerticalSyncEnabled(settings->vSync);

	// Main window loop
	while (window.isOpen())		
	{
		settings->resetTimer();
		if (container.getDraw())
		{
			window.clear(sf::Color::Black);
		}		
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseWheelScrolled:
					container.changeCircleSize(event.mouseWheelScroll.delta);
					break;

				// Redistributes the drawn objects when the window is resized
				case sf::Event::Resized:
					if (container.getLoaded())
					{
						window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
						float diffX = std::max(((int)event.size.width - settings->window.x) / 2, 0);
						float diffY = std::max(((int)event.size.height - settings->window.y) / 2, 0);
						settings->window.x = event.size.width;
						settings->window.y = event.size.height;						
						container.resizedWindow(true);
						container.move(diffX, diffY);
					}
					break;

				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
						case sf::Keyboard::W:
							container.setWrap(!container.getWrap());
							container.resizedWindow(false);
							message->setMessage("Wrapping: " + boolToText(container.getWrap()));
							break;

						case sf::Keyboard::D:
							container.setDraw(!container.getDraw());
							message->setMessage("Trails: " + boolToText(!container.getDraw()));
							break;

						case sf::Keyboard::R:
							container.setRandomPosition();
							message->setMessage("Positions randomised");
							break;
					}
					break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			container.changeCircleSize(-1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			container.changeCircleSize(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			container.changeOpacity(-settings->opacityChange);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			container.changeOpacity(settings->opacityChange);
		}

		if (container.getLoaded())
		{
			container.update();
			window.draw(container);
		}	
		window.display();
	}
	return 0;
}

std::string boolToText(bool input)
{
	return input ? "On" : "Off";
}