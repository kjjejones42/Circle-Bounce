#pragma once

#include "Circle.h"
#include "Message.h"
#include <vector>
#include <thread>
#include "Player.h"

// Container object for the bouncinng Circle objects.
class CircleContainer : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = m_count - 1; i >= 0; --i)
		{
			// Draws each Circle in the container.
			target.draw((*circlesArray)[i], states);
		}
		// Finally draw the Message on top.
		target.draw(message, states);
	}
	// Pointer to the vector that contains the Circles.
	std::vector<Circle>* circlesArray;
	// Pointer to the global Settings object.
	Settings *settings;	
	// The number of Circles in the Container.
	int m_count;
	// Whether the container is fully loaded and has generated all the Circles.
	bool m_loaded = false;
	// The opacity of all the Circles, out of 100.
	int m_opacity;
	// Whether the Circles bounce off the screen borders or wrap around.
	bool m_wrap;
	// Whether the screen is cleared every frame, aka, whether the Circles leave trails.
	bool m_draw;

	// The diameter of the Circles in pixels.
	int m_diameter = 50;
	// The radius of the Circles. Is a seperate variable to cut down on computations.
	double m_radius = static_cast<double>(m_diameter) / 2;

	// Contains the minimum and maximum possible Circle diameters in pixels.
	// The max value should update to match the smallest window dimension.
	struct {
		int min = 1;
		int max = 720;
	} diameterRange;

public:	
	CircleContainer(int c_count = 0);   
	// The Message object that draws messages whenever a variable is changed.
	Message message;
	void setWrap(bool wrap) { m_wrap = wrap; };
	bool getWrap() { return m_wrap; }
	void setDraw(bool draw) { m_draw = draw; }
	bool getDraw() { return m_draw; }
	void setOpacity(int opacity) { m_opacity = opacity; }
	int getOpacity() { return m_opacity; }
	double getRadius() { return m_radius; }
	bool getLoaded() { return m_loaded; }

	// Changes the size of the Circles by a given amount. The parameter is the difference from the current value.
	void changeCircleSize(int num);
	// Resizes all circles to match the current diameter value.
	void resize();
	// Resets each circle position when the window is resized.
	void resizedWindow(bool windowResize);
	// Updates each Circle's position when it is called every frame.
	void update();
	// Updates given quadrant(s) of the CirclesArray.
	// Can be used to seperate the update workload for multithreading.
	void updateSection(int sectionStart, int sectionEnd);
	// Moves all the Circles a given distance in the X and Y dimensions.
	void move(float x, float y);
	// Moves all the Circles to a random position on the screen.
	void setRandomPosition();
	// Changes the opacity (Min:0;Max;100) of the Circles by a given amount. The parameter is the difference from the current value.
	void changeOpacity(int difference);
	// Adds a given number of Circles to the screen. Circles will fade in over a few seconds.
	void addCircles(int num);
	// Resets container to initial values, with zero Circles within.
	void reset();
	
	// Updates the diameter and radius values to match the given diameter value.
	void setDiameter(int n_diam);
	int getDiameter() { return m_diameter; }
	// Updates the Max circle diameter to the smallest window dimension.
	int setResizeRange();
	// Checks if any of the Circles are colliding with the Player.
	bool checkCollision(Player &player);
	
	~CircleContainer();
};