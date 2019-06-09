#pragma once

#include "CircleContainer.h"
#include <vector>
#include <thread>

CircleContainer::CircleContainer(int c_count) : settings(Settings::getInstance()), message(Message::getInstance())
{
	m_count = c_count;
	circlesArray = new std::vector<Circle>(m_count);
	circlesArray->reserve(settings->maxNumObjects);
	m_loaded = true;
}

void CircleContainer::changeCircleSize(int num)
{
	if (m_loaded && num != 0)
	{
		if ((settings->getDiameter() < settings->diameterRange.min && num < 0) || settings->getDiameter() + num < settings->diameterRange.min)
		{
			settings->setDiameter(settings->diameterRange.min);
		}
		else if ((settings->getDiameter() > settings->diameterRange.max && num > 0) || settings->getDiameter() + num > settings->diameterRange.max)
		{
			settings->setDiameter(settings->diameterRange.max);
		}
		else
		{
			settings->setDiameter(settings->getDiameter() + num);
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
	message->setMessage("Size: " + std::to_string(settings->getDiameter()) + "px");
}

void CircleContainer::resizedWindow(bool windowResize)
{
	settings->setResizeRange();
	for (int i = 0; i < m_count; i++)
	{
		(*circlesArray)[i].resizedWindow(windowResize);
	}
	resize();
}

void CircleContainer::update()
{
	if (m_count < settings->maxNumObjects)
	{
		m_count += settings->numObjectsChange;
		circlesArray->resize(m_count);
		for (int i = 0; i < settings->numObjectsChange; i++)
		{
			circlesArray->push_back(Circle());
		}
	}
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
	message->update();
	
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
	if (!((settings->opacity + difference < 1) || (settings->opacity + difference > 100)))
	{
		settings->opacity += difference;
		for (int i = 0; i < m_count; i++)
		{
			(*circlesArray)[i].updateOpacity();
		}
		message->setMessage("Opacity: " + std::to_string(settings->opacity) + "%");
	}
}

CircleContainer::~CircleContainer()
{
	delete circlesArray;
}