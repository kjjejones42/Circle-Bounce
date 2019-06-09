#pragma once

#include "settings.h"

Settings::Settings() :
	m_mersenne(std::mt19937(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()))),
	m_rand(std::uniform_real_distribution<>(0, 1)),
	m_beg(clock_t::now())
{}

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

void Settings::setDiameter(int n_diam)
{
	m_diameter = n_diam;
	m_radius = (float)n_diam / 2;
}
int Settings::setResizeRange()
{
	diameterRange.max = (window.x > window.y ? window.y : window.x) - 1;
	if (m_diameter > diameterRange.max)
	{
		setDiameter(diameterRange.max);
	}
	return diameterRange.max;
}
void Settings::resetTimer()
{
	m_beg = clock_t::now();
}

double Settings::elapsed() const
{
	return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}


float Settings::hue2rgb(float t)
{
	if (t < 0) t += 1.0;
	if (t > 1) t -= 1.0;
	if (t < 1.0 / 6.0) return 6.0 * t;
	if (t < 0.5) return 1.0;
	if (t < 2.0 / 3.0) return (2.0 / 3.0 - t) * 6.0;
	return 0.0;
}

sf::Color Settings::randColor() {
	float h = getRandom(0, 1);
	int r = std::floor(255 * hue2rgb(h + (1.0 / 3.0)));
	int g = std::floor(255 * hue2rgb(h));
	int b = std::floor(255 * hue2rgb(h - (1.0 / 3.0)));
	sf::Color color = sf::Color::Color(
		r < 255 ? r : 255u,
		g < 255 ? g : 255u,
		b < 255 ? b : 255u,
		255u);
	return color;
}
int Settings::seed = 0;

Settings* Settings::m_instance = nullptr;