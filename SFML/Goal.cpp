#include "Goal.h"

Goal::Goal() : settings(Settings::getInstance()), diameter(50)
{
	setFillColor(sf::Color(255, 0, 0, 255));
	setOutlineColor(sf::Color::White);
	setOutlineThickness(-2);
	setRadius(diameter / 2.0);
	setRandomPosition();
}

void Goal::setRandomPosition()
{
	setPosition(
		settings->getRandom(0, settings->window->getSize().x - diameter) + diameter / 2.0,
		settings->getRandom(0, settings->window->getSize().y - diameter) + diameter / 2.0
	);
}

bool Goal::checkCollision(Player &player)
{
	return getGlobalBounds().contains(player.getCollider());
}