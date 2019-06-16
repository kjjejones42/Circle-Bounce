#pragma once

#include "settings.h"

Settings::Settings() :
	m_mersenne(std::mt19937(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()))),
	m_rand(std::uniform_real_distribution<>(0, 1)),
	m_beg(clock_t::now())
{
	font.loadFromMemory(fontNameSpace::fontArray, fontNameSpace::font_length);
}

void Settings::updateSeed()
{
	seed++;
	m_mersenne = std::mt19937(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count() + seed));
}

double Settings::getRandom(float min, float max)
{
	updateSeed();
	double result = (m_rand(m_mersenne));
	return result * (max - min) - min;
}

Settings* Settings::getInstance() {
	if (!m_instance)
		m_instance = new Settings();
	return m_instance;
}

void Settings::resetTimer()
{
	m_beg = clock_t::now();
}

double Settings::elapsed() const
{
	return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

float Settings::hue2rgb(float p, float q, float t)
{
	if (t < 0) t += 1.0;
	if (t > 1) t -= 1.0;
	if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
	if (t < 1.0 / 2.0) return q;
	if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
	return p;
}


sf::Color Settings::hslToRgb(float h, float s, float l)
{
	float r, g, b;

	if(s == 0)
	{
		r = g = b = l;
	}
	else
	{
		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = hue2rgb(p, q, h + 1.0/3.0);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1.0/3.0);
	}
	return sf::Color((unsigned int)std::round(r * 255), (unsigned int)std::round(g * 255), (unsigned int)std::round(b * 255));
}


int Settings::seed = 0;

Settings* Settings::m_instance = nullptr;