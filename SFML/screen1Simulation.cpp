#pragma once

#include "screen1Simulation.h"
#include "cScreen.h"
#include <iostream>
#include "Title.h";

void screen1Simulation::reset() {};

screen1Simulation::screen1Simulation() : settings(Settings::getInstance()), container(CircleContainer(settings->minNumObjects)) {}

int screen1Simulation::Run(sf::RenderWindow &window)
{
	Title title;
	title.addMessage("SIMULATION CONTROLS")
		.addMessage("\n")
		.addMessage("D - Draw trails.")
		.addMessage("W - Wrap around the screen.")
		.addMessage("R - Reset position.")
		.addMessage("Up & Down Arrows - Change size.")
		.addMessage("Left & Right Arrows - Change opacity.")
		.addMessage("\n")
		.addMessage("Press Esc to pause, and press Esc again to return to the start screen.");

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(0, 0, 0, 255 * 0.8));

	bool onTitleMessage = true;
	while (true)
	{
		rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		if (container.getDraw())
		{
			window.clear(sf::Color::Black);
		}
		sf::Event event;
		if (onTitleMessage)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
				{
					if (event.key.code == sf::Keyboard::Escape) return cScreen::START;
					onTitleMessage = false;
					break;
				}

				case sf::Event::Closed:
					return cScreen::EXIT_PROGRAM;

				case sf::Event::Resized:
				{
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
					break;
				}
				}
			}
			window.draw(container);
			window.draw(rect);
			window.draw(title);
			window.display();
		}
		else
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
					return cScreen::EXIT_PROGRAM;

				case sf::Event::MouseWheelScrolled:
					container.changeCircleSize(event.mouseWheelScroll.delta);
					break;

					// Redistributes the drawn objects when the window is resized
				case sf::Event::Resized:
					if (container.getLoaded())
					{
						window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
						float diffX = std::max(((int)event.size.width - settings->previousWindowWidth) / 2, 0);
						float diffY = std::max(((int)event.size.height - settings->previousWindowHeight) / 2, 0);
						settings->previousWindowWidth = event.size.width;
						settings->previousWindowHeight = event.size.height;
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
						container.message.setMessage("Wrapping: " + boolToText(container.getWrap()));
						break;

					case sf::Keyboard::D:
						container.setDraw(!container.getDraw());
						container.message.setMessage("Trails: " + boolToText(!container.getDraw()));
						break;

					case sf::Keyboard::R:
						container.setRandomPosition();
						container.message.setMessage("Positions randomised");
						break;

					case sf::Keyboard::Escape:
						onTitleMessage = true;
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
				container.changeOpacity(-1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				container.changeOpacity(1);
			}

			if (container.getLoaded())
			{
				container.addCircles(settings->numObjectsChange);
				container.update();
				window.draw(container);
			}
			window.display();
		}
	}
	return cScreen::EXIT_PROGRAM;
}

std::string boolToText(bool input)
{
	return input ? "On" : "Off";
}