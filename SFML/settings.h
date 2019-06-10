#pragma once

#include <SFML/Graphics.hpp>
#include <random> 
#include <chrono>

class Settings
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1, 1> >;

	static Settings* m_instance;	
	std::mt19937 m_mersenne;
	std::uniform_real_distribution<> m_rand;
	int m_diameter = 50;
	double m_radius = static_cast<double>(m_diameter) / 2;
	float hue2rgb(float t);

	static int seed;
	
	Settings();

public:	

	static Settings *getInstance();

	const bool multithreading = false;
	const bool vSync = true;
	const int opacityChange = 1;
	const int minNumObjects = 0;
	const int maxNumObjects = 5000;
	const int numObjectsChange = 10;
	const int messageOpacityChange = 10;
	const int messageDuration = 1;
	const int maxMomentum = 5;
	const double minSpeed = 1.0;
	const int initialOpacity = 50;
	
	bool draw = true;
	bool wrap = true;		
	std::chrono::time_point<clock_t> m_beg;

	struct {
		int x = 1280;
		int y = 720;
	} window;
	struct {
		int min = 1;
		int max = 720;
	} diameterRange;

	void setDiameter(int n_diam);
	int getDiameter() { return m_diameter; }
	double getRadius() { return m_radius; }
	int setResizeRange();
	double getRandom(float min, float max);
	void resetTimer();
	double elapsed() const;
	sf::Color randColor();
	void updateSeed();
};
