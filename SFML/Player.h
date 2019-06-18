#pragma once

#include "SFML/Graphics.hpp"
#include "settings.h"
#include <math.h>  

// SFML Vertex-Array Object that represents the arrowhead player object.
class Player : public sf::Transformable, public sf::Drawable
{
private:
	// Draws the player object to the screen.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(vertices, states);
	}
	// Array that contains the object vertices.
	sf::VertexArray vertices;
	// Pointer to the global settings object.
	Settings* settings;
	// Co-ordinate - the player moves towards this point every update.
	sf::Vector2i seekPoint;
	// Momentum quality, not yet implemented.
	sf::Vector2f momentum;

public:
	// Allows you to set which coordinate the player object moves towards.
	void setSeekPoint(sf::Vector2i(pos)) { seekPoint = pos; }
	virtual sf::Vector2f getPoint(std::size_t index) const;
	virtual std::size_t getPointCount() const { return 4; }
	// Returns the coordinates of the vertex at the head of the arrow - for collision detection.
	sf::Vector2f getCollider();
	// Updates the player position and rotation when called.
	void update();
	// Moves the player object to the centre of the screen.
	void recentreIcon();
	Player();
};

