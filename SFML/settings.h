#pragma once

#include <SFML/Graphics.hpp>
#include <random> 
#include <chrono>
#include "cScreen.h"
#include "font.h"

// This is a singleton class that contains global settings and functions. Call getInstance() to get a pointer to the settings object
class Settings
{
	// These allow time methods to be used less verbosely
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1, 1> >;

	// Pointer to the singleton Settings instance
	static Settings* m_instance;	

	// Variables that together make up the timer
	std::mt19937 m_mersenne;
	std::uniform_real_distribution<> m_rand;
	static int seed;

	// Intermediary function used by hslToRgb
	float hue2rgb(float p, float q, float t);

	// Private constructor, so only method to get this object is via getInstance()
	Settings();

public:	

	// Generates one instance of the Settings object if none exists already.
	// Returns pointer to this instance 
	static Settings* getInstance();
	
	// Font object used for all the text objects in this project
	sf::Font font;

	// GLOBAL SETTINGS - these constant variables are the program settings
	
	// Enables / disable multithreaded Circle updating. Was found to negatively affect performance, false by default.
	const bool multithreading = false;
	const bool vSync = true;
	// The min amount, max amount, and rate of change of the circles in the Simulation mode
	const int minNumObjects = 0;
	const int maxNumObjects = 5000;
	const int numObjectsChange = 10;
	// How many seconds the simulation update messages stay before starting to fade
	const int messageDuration = 1;
	// How quickly the simulation update messages fade after they've expired
	const int messageOpacityChange = 10;
	// Speed variables used for the moving circles
	const int maxMomentum = 5;
	const double minSpeed = 1.0;
	// Initial opacity out of 100 of the circles.
	const int initialOpacity = 50;
	// Initial values for whether circles leave trails and/or wrap around the screen
	const bool initialDraw = true;
	const bool initialWrap = false;
	// Initial diameter of the circles, in pixels
	const int initialDiameter = 50;
	// Initial window size
	const int initialWindowWidth = 1280;
	const int initialWindowHeight = 720;
	// The program's starting screen
	const cScreen::screenName initialScreen = cScreen::START;
	// Time point variable. To allow timing.
	std::chrono::time_point<clock_t> m_beg;
	// Pointer to the main window object, to allow access by other variables.
	sf::RenderWindow* window;

	// Variables to keep track of window size, to be updated whenever window resizes.
	int previousWindowWidth = initialWindowWidth;
	int previousWindowHeight = initialWindowHeight;

	// Returns a random number.
	double getRandom(float min, float max);
	// Timer access functions
	void resetTimer();
	double elapsed() const;
	void updateSeed();
	// Returns a SFML color object that corresponds to a given hue, saturation, and lightness.
	sf::Color hslToRgb(float h, float s, float l);
};
