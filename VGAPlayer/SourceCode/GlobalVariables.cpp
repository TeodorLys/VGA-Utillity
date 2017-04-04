#include "GlobalVariables.h"
#include "InitialSetup.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <string>

using namespace std;

namespace GV {
	sf::RenderWindow window;
    sfe::Movie movie;
	sfe::Movie movie2;
	InitialSetup init;
	string moviePath;
	string APTpath;

	const short uiIndex = 4;
}

