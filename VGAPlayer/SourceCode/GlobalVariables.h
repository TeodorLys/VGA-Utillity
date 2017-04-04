#pragma once
#include "InitialSetup.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <string>

namespace GV {
	extern sf::RenderWindow window;
	extern sfe::Movie movie;
	extern sfe::Movie movie2;
	extern InitialSetup init;
	extern const short uiIndex;
	extern std::string moviePath;
	extern std::string APTpath;
}

