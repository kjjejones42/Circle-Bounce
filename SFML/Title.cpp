#pragma once

#include "Title.h"

Title& Title::addMessage(std::string string)
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
	text.move(settings->window->getSize().x / 2.0, 0);
	textArray.push_back(text);
	recalculatePosition();
	return *this;
}

void Title::recalculatePosition()
{
	float midpoint = textArray.size() / 2.0;
	for (int i = 0, n = textArray.size(); i < n; ++i)
	{		
		sf::Vector2f position = textArray[i].getPosition();
		position.y = settings->window->getSize().y / 2.0 + (i - midpoint) * lineSpacing;
		position.x = settings->window->getSize().x / 2.0;
		textArray[i].setPosition(position);
	}
}

void Title::move(double x, double y)
{
	for (sf::Text &text : textArray)
	{
		text.move(x, y);
	}
}
