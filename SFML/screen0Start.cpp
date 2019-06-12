#include "screen0Start.h"
#include "settings.h"
#include "font.h"
#include <iostream>

class Title : public sf::Drawable
{
	std::vector<sf::Text> textArray;
	sf::RectangleShape textBackground;
	Settings *settings;

public:
	Title() : settings(Settings::getInstance())
	{
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(textBackground, states);
		for (int i = 0; i < textArray.size(); i++)
		{
			target.draw(textArray[i], states);
		}
	}
	Title& addMessage(std::string string)
	{
		int index = textArray.size();
		sf::Text text = sf::Text(string, settings->font);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1.0);
		text.setLetterSpacing(0.9);
		text.setOrigin(
			text.getGlobalBounds().width / 2.0,
			text.getGlobalBounds().height / 2.0
		);
		text.move(
			settings->window.x / 2.0,
			settings->window.y / 4.0 + index * 40
		);
		textArray.push_back(text);
		return *this;
	}
	void move(double x, double y)
	{
		for (sf::Text &text : textArray)
		{
			
			text.move(x, y);
		}
	}
};

int screen0Start::Run(sf::RenderWindow &window)
{
	Settings* settings = Settings::getInstance();
	double randColor = settings->getRandom(0, 1);
	Title title;
	title.addMessage("Welcome to Circle Bounce!")
		.addMessage("Press any button to start.")
		.addMessage("Or don't, I'm not a cop.")
		.addMessage("\n")
		.addMessage("D - Draw trails.")
		.addMessage("W - Wrap around the screen.")
		.addMessage("R - Reset position.")
		.addMessage("Up & Down Arrows - Change size.")
		.addMessage("Left & Right Arrows - Change opacity.");

	while (true)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		rectangle.setPosition(0, 0);
		rectangle.setFillColor(sf::Color(0u,0u,0u,(unsigned int)(255*0.95)));
		window.clear(settings->randColor(std::fmod(randColor += 0.001, 1.0)));
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					return cScreen::EXIT;

				case sf::Event::KeyReleased:
					return cScreen::SIMULATION;

				case sf::Event::Resized:
				{
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
					double diffX = (int)event.size.width - settings->window.x;
					title.move(diffX / 2.0, 0.0);
					settings->window.x = event.size.width;
					settings->window.y = event.size.height;
					break;
				}
			}
		}
		window.draw(rectangle);
		window.draw(title);
		window.display();
	}
	return cScreen::EXIT;
}