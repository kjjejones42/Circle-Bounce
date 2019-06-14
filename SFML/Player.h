#pragma once

#include "SFML/Graphics.hpp"
#include "settings.h"

class Player : public sf::Transformable, public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(vertices, states);
	}
	sf::VertexArray vertices;
	Settings* settings;
	sf::Vector2i seekPoint;
	sf::Vector2f momentum;

public:
	void setSeekPoint(sf::Vector2i(pos)) { seekPoint = pos; }
	virtual sf::Vector2f getPoint(std::size_t index) const;
	virtual std::size_t getPointCount() const { return 4; }
	void update();
	Player();
};

