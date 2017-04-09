#include "GlobalVariables.h"
#include "Actions.h"
#include "fanArt.h"
#include "InitialSetup.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <string>

using namespace std;

namespace GV {
	sf::RenderWindow window;
	sf::Mouse mouse;
    sfe::Movie movie;
	sfe::Movie movie2;
	InitialSetup initial;
	Actions actions;

	string moviePath;
	string APTpath;
	fanArt fa;
	sf::Texture ffsBG;
	sf::RectangleShape ffssp[2];

	sf::Text vol1;
	sf::Text vol2;
	sf::Font font;
	sf::Text OMov;
	sf::Text OVGA;
	sf::Text tPlay;
	sf::Color COMov = sf::Color(255, 255, 255);
	sf::Color COVGA = sf::Color(255, 255, 255);
	sf::Sprite stest;
	sf::Texture te;

	float width = 1080;
	float height = 720;

	float w;
	float h;
	const short uiIndex = 4;
}

