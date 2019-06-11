#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "font.h"

class Message : public sf::Drawable
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1, 1> >;

	sf::Text text;
	sf::RectangleShape textBackground;
	Settings *settings;
	int opacity;	
	std::chrono::time_point<clock_t> messageTimer;
	std::chrono::duration<int> messageDuration;
	bool expired = true;

public:
	Message();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(textBackground, states);
		target.draw(text, states);
	}
	void recalcBackgroundSize();
	void setMessage(std::string message);
	void setOpacity(int opacity);
	void update();	
};