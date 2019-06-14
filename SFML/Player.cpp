#include "Player.h"
#include <iostream>


Player::Player(): vertices(sf::VertexArray(sf::TrianglesFan, 4)), settings(Settings::getInstance())
{
	for (int i = 0; i < 4; i++)
	{
		vertices[i].position = getPoint(i);
	}
	vertices[0].color = sf::Color::Black;
	
	move(settings->window->getSize().x / 2.0, settings->window->getSize().y / 2.0);
}

void Player::update()
{
}

sf::Vector2f Player::getPoint(std::size_t index) const
{
	switch (index)
	{
		case 0: return sf::Vector2f(0.f, 11.f);
		case 1: return sf::Vector2f(-30.f, 50.f);
		case 2: return sf::Vector2f(0.f, -40.f);
		case 3: return sf::Vector2f(30.f, 50.f);
	}
	return sf::Vector2f(0, 0);
}