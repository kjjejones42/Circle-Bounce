#include "screen2Game.h"
#include "settings.h"

int screen2Game::Run(sf::RenderWindow &window)
{
	Settings* settings = Settings::getInstance();
	double randColor = settings->getRandom(0, 1);

	// create an array of 3 vertices that define a triangle primitive

	sf::VertexArray triangle(sf::TrianglesFan, 4);
	
	// define the position of the triangle's points
	triangle[0].position = sf::Vector2f(0.f, 11.f);
	triangle[1].position = sf::Vector2f(-30.f, 50.f);
	triangle[2].position = sf::Vector2f(0.f, -40.f);
	triangle[3].position = sf::Vector2f(30.f, 50.f);

	// define the color of the triangle's points
	triangle[0].color = sf::Color::Black;


	sf::Transform transform;
	transform.translate(settings->window->getSize().x / 2.0, settings->window->getSize().y / 2.0);
	
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
					float diffX = ((int)event.size.width - settings->previousWindowWidth) / 2;
					float diffY = ((int)event.size.height - settings->previousWindowHeight) / 2;
					settings->previousWindowWidth = event.size.width;
					settings->previousWindowHeight = event.size.height;
					transform.translate(diffX, diffY);
					break;
				}
			}
		}
		window.draw(triangle, transform);
		window.display();
	}
	return cScreen::EXIT_PROGRAM;
}