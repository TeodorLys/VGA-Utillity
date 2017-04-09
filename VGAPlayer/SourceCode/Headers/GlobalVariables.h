#pragma once
#include "InitialSetup.h"
#include "Actions.h"
#include "fanArt.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <string>

namespace GV {
	extern sf::RenderWindow window;
	extern sf::Mouse mouse;
	extern sfe::Movie movie;
	extern sfe::Movie movie2;
	extern InitialSetup initial;
	extern Actions actions;
	extern fanArt fa;
	extern float w;
	extern float h;
	extern float width;
	extern float height;

	extern const short uiIndex;
	extern std::string moviePath;
	extern std::string APTpath;
	extern sf::Text vol1;
	extern sf::Text vol2;
	extern sf::Font font;
	extern sf::Text OMov;
	extern sf::Text OVGA;
	extern sf::Text tPlay;
	extern sf::Sprite stest;
	extern sf::Texture te;

	extern sf::Color COMov;
	extern sf::Color COVGA;

	extern sf::Texture ffsBG;
	extern sf::RectangleShape ffssp[2];
}

