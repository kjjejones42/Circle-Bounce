#pragma once

#include "Circle.h"
#include "CircleContainer.h"
#include <iostream>

void Circle::init()
{
	loadProgress = 0.0;
	loading = true;
	settings = Settings::getInstance();

	double angle = (settings->getRandom(0, 360)) * 3.14f / 180.f;
	double speed = (settings->getRandom(0, settings->maxMomentum)) + settings->minSpeed;
	momentum = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

	setRadius(parent->getRadius());
	setOrigin(parent->getRadius(), parent->getRadius());
	setRandomPosition();

	sf::Color color = settings->randColor(settings->getRandom(0,1));
	setFillColor(color);
	updateOpacity();
}

Circle::Circle(CircleContainer* const c_parent) : parent(c_parent)
{	
	init();

}

Circle::Circle() : parent(nullptr)
{
	init();
}

bool Circle::isInValidArea()
{
	sf::Vector2f position = getPosition();
	double radius = loadProgress * parent->getRadius();
	return !(position.x < radius || position.y < radius || position.x >(settings->window.x - radius) || position.y >(settings->window.y - radius));
}

void Circle::setRandomPosition()
{
	setPosition(
		settings->getRandom(0, settings->window.x - loadProgress * parent->getDiameter()) + loadProgress * parent->getRadius(),
		settings->getRandom(0,settings->window.y - loadProgress * parent->getDiameter()) + loadProgress * parent->getRadius()
	);
}
void Circle::resize()
{
	setRadius(parent->getRadius() * loadProgress);
	setOrigin(parent->getRadius() * loadProgress, parent->getRadius() * loadProgress);
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
	
	double radius = parent->getRadius();
	sf::Vector2f position = getPosition();

	if (parent->getWrap())
	{
		// If wrap setting is selected, ensures that the object's position wraps around
		position.x += settings->window.x + parent->getDiameter();
		position.y += settings->window.y + parent->getDiameter();
		setPosition(
			fmod(position.x + parent->getRadius(), settings->window.x + parent->getDiameter()) - parent->getRadius(),
			fmod(position.y + parent->getRadius(), settings->window.y + parent->getDiameter()) - parent->getRadius()
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

	double radius = parent->getRadius();
	int windowX = settings->window.x;
	int windowY = settings->window.y;

	// Changes position if the window is resized to a smaller size
	if (!isInValidArea())
	{
		sf::Vector2f position = getPosition();
		if (windowResize)
		{
			position.x = fmod((position.x), (windowX - parent->getDiameter()));
			position.y = fmod((position.y), (windowY - parent->getDiameter()));

			float offsetX = position.x > (windowX - radius) ? -radius : (position.x < radius ? radius : 0.f);
			float offsetY = position.y > (windowY - radius) ? -radius : (position.y < radius ? radius : 0.f);

			setPosition(position.x + offsetX, position.y + offsetY);
		}
		else
			if (parent->getWrap())
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
	color.a = static_cast<unsigned int>(255.0 / 100.0 * (double)parent->getOpacity() * loadProgress);
	setFillColor(color);	
}
