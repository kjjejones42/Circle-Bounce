#pragma once

#include "Message.h"

Message::Message() : settings(Settings::getInstance())
{
	messageDuration = std::chrono::duration<int>(settings->messageDuration);
	font.loadFromMemory(fontNameSpace::fontArray, fontNameSpace::font_length);

	text = sf::Text("", font);
	text.setScale(0.66, 0.66);
	text.setFillColor(sf::Color::White);
	text.setLetterSpacing(0.9);
	text.move(5.0, 0.0);

	textBackground.setFillColor(sf::Color::Black);
	textBackground.setOutlineColor(sf::Color::White);
	textBackground.setOutlineThickness(1.f);

	recalcBackgroundSize();
	setOpacity(0);
	messageTimer = std::chrono::high_resolution_clock::now();
}


void Message::recalcBackgroundSize()
{
	textBackground.setSize(sf::Vector2f(
		text.getPosition().x + text.getGlobalBounds().width + 10.0,
		text.getPosition().y + 27.0
	));
}
void Message::setMessage(std::string message)
{
	expired = false;
	text.setString(message);
	recalcBackgroundSize();
	setOpacity(255);
}
void Message::setOpacity(int c_opacity)
{
	
	opacity = c_opacity;
	if (opacity < 0) opacity = 0;
	if (opacity > 255) opacity = 255;

	sf::Color tColor = text.getFillColor();
	sf::Color bColor = textBackground.getFillColor();
	sf::Color bfColor = textBackground.getOutlineColor();
	bColor.a = opacity;
	bfColor.a = opacity;
	tColor.a = opacity;
	text.setFillColor(tColor);
	textBackground.setFillColor(bColor);
	textBackground.setOutlineColor(bfColor);

	messageTimer = std::chrono::high_resolution_clock::now();
}
void Message::update()
{
	if (opacity > 0)
	{
		if (!expired)
		{
			expired = (std::chrono::duration_cast<second_t>(clock_t::now() - messageTimer) > messageDuration);
		}
		else
		{
			setOpacity(opacity - settings->messageOpacityChange);
		}

	}
}
