#include "Player.h"

#define PI 3.14159265

Player::Player(): vertices(sf::VertexArray(sf::TrianglesFan, 4)), settings(Settings::getInstance())
{
	for (int i = 0; i < 4; i++)
	{
		vertices[i].position = getPoint(i);
	}
	vertices[0].color = sf::Color(0,0,0,0);
	
	move(settings->window->getSize().x / 2.0, settings->window->getSize().y / 2.0);
}


void Player::update()
{
	sf::Vector2f position = getPosition();
	sf::Vector2f difference = sf::Vector2f(seekPoint) - position;
	float newAngle = fmod(180.0 - atan2(difference.x, difference.y) * 180 / PI, 360.0);
	setRotation(newAngle);
;	move((seekPoint.x - position.x) / 30.0, (seekPoint.y - position.y) / 30.0);
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

sf::Vector2f Player::getCollider()
{
	return getTransform().transformPoint(vertices[2].position);
}
void Player::recentreIcon()
{
	setPosition(settings->window->getSize().x / 2.0, settings->window->getSize().y / 2.0);
}