#pragma once

#include "Circle.h"

Circle::Circle(CircleContainer* c_parent) : settings(Settings::getInstance()), parent(c_parent), loading(true), loadProgress(0.0)
{	
	double angle = (settings->getRandom(0, 360)) * 3.14f / 180.f;
	double speed = (settings->getRandom(0, settings->maxMomentum)) + settings->minSpeed;
	momentum = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

	setRadius(settings->getRadius());
	setOrigin(settings->getRadius(), settings->getRadius());
	setRandomPosition();

	sf::Color color = settings->randColor();
	setFillColor(color);
	updateOpacity();
}

bool Circle::isInValidArea()
{
	sf::Vector2f position = getPosition();
	double radius = loadProgress * settings->getRadius();
	return !(position.x < radius || position.y < radius || position.x >(settings->window.x - radius) || position.y >(settings->window.y - radius));
}

void Circle::setRandomPosition()
{
	setPosition(
		settings->getRandom(0, settings->window.x - loadProgress * settings->getDiameter()) + loadProgress * settings->getRadius(),
		settings->getRandom(0,settings->window.y - loadProgress * settings->getDiameter()) + loadProgress * settings->getRadius()
	);
}
void Circle::resize()
{
	setRadius(settings->getRadius() * loadProgress);
	setOrigin(settings->getRadius() * loadProgress, settings->getRadius() * loadProgress);
	if (!isInValidArea())
	{
		resizedWindow(false);
	}
}
void Circle::update()
{	
	if (loading)
	{		
		loadProgress += 0.01;
		if (loadProgress >= 1.0) 
		{
			loading = false;
			loadProgress = 1.0;
		}
		updateOpacity();
		resize();
	}
	
	double radius = settings->getRadius();
	sf::Vector2f position = getPosition();

	if (settings->wrap)
	{
		// If wrap setting is selected, ensures that the object's position wraps around
		position.x += settings->window.x + settings->getDiameter();
		position.y += settings->window.y + settings->getDiameter();
		setPosition(
			fmod(position.x + settings->getRadius(), settings->window.x + settings->getDiameter()) - settings->getRadius(),
			fmod(position.y + settings->getRadius(), settings->window.y + settings->getDiameter()) - settings->getRadius()
		);
	}
	else
	{
		// Makes object bounce off of the walls.
		if (position.x >= settings->window.x - radius)
		{
			momentum.x = -std::abs(momentum.x);
		}
		else if (position.x <= radius)
		{
			momentum.x = std::abs(momentum.x);
		}
		if (position.y >= settings->window.y - radius)
		{
			momentum.y = -std::abs(momentum.y);
		}
		else if (position.y <= radius)
		{
			momentum.y = std::abs(momentum.y);
		}
	}
	move(
		settings->minSpeed * momentum.x,
		settings->minSpeed * momentum.y
	);
}
void Circle::resizedWindow(bool windowResize){

	double radius = settings->getRadius();
	int windowX = settings->window.x;
	int windowY = settings->window.y;

	// Changes position if the window is resized to a smaller size
	if (!isInValidArea())
	{
		sf::Vector2f position = getPosition();
		if (windowResize)
		{
			position.x = fmod((position.x), (windowX - settings->getDiameter()));
			position.y = fmod((position.y), (windowY - settings->getDiameter()));

			float offsetX = position.x > (windowX - radius) ? -radius : (position.x < radius ? radius : 0.f);
			float offsetY = position.y > (windowY - radius) ? -radius : (position.y < radius ? radius : 0.f);

			setPosition(position.x + offsetX, position.y + offsetY);
		}
		else
			if (settings->wrap)
			{
				setRandomPosition();				
			}
			else
			{
				float distanceToEdgeX = (position.x < windowX / 2) ? position.x : -(windowX - position.x);
				float distanceToEdgeY = (position.y < windowY / 2) ? position.y : -(windowY - position.y);
				float newX = (abs(distanceToEdgeX) < radius) ? (distanceToEdgeX > 0 ? radius : windowX - radius) : position.x;
				float newY = (abs(distanceToEdgeY) < radius) ? (distanceToEdgeY > 0 ? radius : windowY - radius) : position.y;

				setPosition(newX, newY);
			}
	}
}
void Circle::updateOpacity()
{
	sf::Color color = getFillColor();
	color.a = static_cast<unsigned int>(255.0 / 100.0 * (double)settings->opacity * loadProgress);
	setFillColor(color);	
}
