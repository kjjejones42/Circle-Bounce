#pragma once

#include "Circle.h"
#include "Message.h"

class CircleContainer : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = m_count - 1; i >= 0; --i)
		{
			target.draw((*circlesArray)[i], states);
		}
		target.draw(message, states);
	}
	std::vector<Circle>* circlesArray;
	Settings *settings;	
	int m_count;
	bool m_loaded = false;
	int m_opacity;
	bool m_wrap;
	bool m_draw;

	int m_diameter = 50;
	double m_radius = static_cast<double>(m_diameter) / 2;

	struct {
		int min = 1;
		int max = 720;
	} diameterRange;

public:	
	CircleContainer(int c_count);   
	
	Message message;
	void setWrap(bool wrap) { m_wrap = wrap; };
	bool getWrap() { return m_wrap; }
	void setDraw(bool draw) { m_draw = draw; }
	bool getDraw() { return m_draw; }
	void setOpacity(int opacity) { m_opacity = opacity; }
	int getOpacity() { return m_opacity; }
	double getRadius() { return m_radius; }
	bool getLoaded() { return m_loaded; }

	void changeCircleSize(int num);
	void resize();
	void resizedWindow(bool windowResize);
	void update();
	void updateSection(int sectionStart, int sectionEnd);
	void move(float x, float y);
	void setRandomPosition();
	void changeOpacity(int difference);
	void addCircles(int num);
	
	void setDiameter(int n_diam);
	int getDiameter() { return m_diameter; }
	int setResizeRange();
	
	~CircleContainer();
};