#pragma once

#include "CircleContainer.h"
#include <vector>
#include <thread>
#include <iostream>

CircleContainer::CircleContainer(int c_count) : settings(Settings::getInstance()), message(Message())
{
	m_opacity = settings->initialOpacity;
	m_draw = settings->initialDraw;
	m_wrap = settings->initialWrap;
	m_count = c_count;
	circlesArray = new std::vector<Circle>;
	circlesArray->push_back(Circle(this));
	circlesArray->reserve(settings->maxNumObjects);
	m_loaded = true;
}

void CircleContainer::changeCircleSize(int num)
{
	if (m_loaded && num != 0)
	{
		if ((getDiameter() < diameterRange.min && num < 0) || getDiameter() + num < diameterRange.min)
		{
			setDiameter(diameterRange.min);
		}
		else if ((getDiameter() > diameterRange.max && num > 0) || getDiameter() + num > diameterRange.max)
		{
			setDiameter(diameterRange.max);
		}
		else
		{
			setDiameter(getDiameter() + num);
		}
		resize();
	}
}

void CircleContainer::resize()
{
	for (int i = 0; i < m_count; i++)
	{
		(*circlesArray)[i].resize();
	}
	message.setMessage("Size: " + std::to_string(getDiameter()) + "px");
}

void CircleContainer::resizedWindow(bool windowResize)
{
	setResizeRange();
	for (int i = 0; i < m_count; i++)
	{
		(*circlesArray)[i].resizedWindow(windowResize);
	}
	resize();
}

void CircleContainer::addCircles(int num)
{
	if (m_count < settings->maxNumObjects)
	{
		m_count += num;
		for (int i = 0; i < num; i++)
		{
			circlesArray->push_back(Circle(this));
		}
	}
}

void CircleContainer::update()
{
	if (settings->multithreading)
	{
		std::thread t1(&CircleContainer::updateSection, this, 0, 1);
		std::thread t2(&CircleContainer::updateSection, this, 1, 2);
		std::thread t3(&CircleContainer::updateSection, this, 2, 3);
		std::thread t4(&CircleContainer::updateSection, this, 3, 4);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
	else
	{
		updateSection(0, 4);
	}
	message.update();
	
}

void CircleContainer::updateSection(int sectionStart, int sectionEnd)
{
	float numObjectsDiv4 = m_count / 4.0;
	float min = sectionStart * numObjectsDiv4;
	float max = sectionEnd * numObjectsDiv4;
	for (int i = std::round(min); i < max; i++)
	{
		(*circlesArray)[i].update();
	}
}

void CircleContainer::move(float x, float y)
{
	for (int i = 0; i < m_count; i++)
	{
		(*circlesArray)[i].move(x, y);
	}
}

void CircleContainer::setRandomPosition()
{
	for (int i = 0; i < m_count; i++)
	{
		(*circlesArray)[i].setRandomPosition();
	}
}

void CircleContainer::changeOpacity(int difference)
{
	if (!((getOpacity() + difference < 1) || (getOpacity() + difference > 100)))
	{
		setOpacity(getOpacity() + difference);
		for (int i = 0; i < m_count; i++)
		{
			(*circlesArray)[i].updateOpacity();
		}
		message.setMessage("Opacity: " + std::to_string(getOpacity()) + "%");
	}
}


void CircleContainer::setDiameter(int n_diam)
{
	m_diameter = n_diam;
	m_radius = (float)n_diam / 2;
}
int CircleContainer::setResizeRange()
{
	diameterRange.max = (settings->window->getSize().x > settings->window->getSize().y ? settings->window->getSize().y : settings->window->getSize().x) - 1;
	if (m_diameter > diameterRange.max)
	{
		setDiameter(diameterRange.max);
	}
	return diameterRange.max;
}


CircleContainer::~CircleContainer()
{
	delete circlesArray;
}