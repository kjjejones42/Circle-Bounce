#pragma once

#include <SFML/Graphics.hpp>
#include <random> 
#include <chrono>
#include "cScreen.h"
#include "font.h"

class Settings
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1, 1> >;

	static Settings* m_instance;	
	std::mt19937 m_mersenne;
	std::uniform_real_distribution<> m_rand;
	float hue2rgb(float p, float q, float t);
	static int seed;
	Settings();

public:	

	static Settings* getInstance();
	
	sf::Font font;
	const bool multithreading = false;
	const bool vSync = true;
	const int minNumObjects = 0;
	const int maxNumObjects = 5000;
	const int numObjectsChange = 10;
	const int messageOpacityChange = 10;
	const int messageDuration = 1;
	const int maxMomentum = 5;
	const double minSpeed = 1.0;
	const int initialOpacity = 50;	
	const bool initialDraw = true;
	const bool initialWrap = false;
	const int initialDiameter = 50;
	const int initialWindowWidth = 1280;
	const int initialWindowHeight = 720;
	const cScreen::screenName initialScreen = cScreen::START;
	std::chrono::time_point<clock_t> m_beg;
	sf::RenderWindow* window;

	int previousWindowWidth = initialWindowWidth;
	int previousWindowHeight = initialWindowHeight;

	double getRandom(float min, float max);
	void resetTimer();
	double elapsed() const;
	void updateSeed();
	sf::Color hslToRgb(float h, float s, float l);
};
