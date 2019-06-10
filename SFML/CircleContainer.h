#pragma once


#include "Circle.h"
#include "Message.h"

class CircleContainer : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < m_count ; i++)
		{
			target.draw((*circlesArray)[i], states);
		}
		target.draw(*message, states);
	}
	std::vector<Circle>* circlesArray;
	Settings *settings;	
	int m_count;
	bool m_loaded = false;
	Message *message = nullptr;
	int m_opacity;
	bool m_wrap;
	bool m_draw;

public:	
	CircleContainer(int c_count);   

	Message* getMessageHandler() { return message; }
	void setWrap(bool wrap) { m_wrap = wrap; };
	bool getWrap() { return m_wrap; }
	void setDraw(bool draw) { m_draw = draw; }
	bool getDraw() { return m_draw; }
	void setOpacity(int opacity) { m_opacity = opacity; }
	int getOpacity() { return m_opacity; }

	bool getLoaded() { return m_loaded; }

	void changeCircleSize(int num);
	void resize();
	void resizedWindow(bool windowResize);
	void update();
	void updateSection(int sectionStart, int sectionEnd);
	void move(float x, float y);
	void setRandomPosition();
	void changeOpacity(int difference);
	
	~CircleContainer();
};