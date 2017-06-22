#include "keyPress.h"
#include "GlobalVariables.h"
#include <iostream>

using namespace std;
using namespace GV;

void keyPress::press(sf::Event event, sf::Time time) {

	switch (event.key.code) {
		///If the user clicks SPACE
	case sf::Keyboard::Space:
		///Checks if the movie is playing
		if (sfemov.movie->getStatus() == sfe::Playing) {

			//Pauses the movies if it is playing
			sfemov.movie->pause();

			if (mod.oneMovie->switchON && bools.movie2Active)
				sfemov.movie2->pause();
		}
		else {
			//If the movie isnt playing, play them
			sfemov.movie->play();

			if (mod.oneMovie->switchON && bools.movie2Active)
				sfemov.movie2->play();
		}
		break;
		///If the user clicks the 'F' key
	case sf::Keyboard::F:
		if (!bools.isFullscreen) {
			//Runs the Enter Fullscreen function
			enterFullscreen(sfm.window);
			bools.isFullscreen = true;
		}
		else {
			//Runs the Exit Fullscreen function
			exitFullscreen(sfm.window);
			bools.isFullscreen = false;
		}
		break;

		///If the user clicks the right arrow button
	case sf::Keyboard::Right:
		//gets the current playing time
		time = sf::seconds(sfemov.movie->getPlayingOffset().asSeconds());
		value.inc = 10;

		if (sfemov.movie->getDuration().asSeconds() - sfemov.movie->getPlayingOffset().asSeconds() < 10) {
			value.inc = sfemov.movie->getDuration().asSeconds() - sfemov.movie->getPlayingOffset().asSeconds() - 1;
			cout << value.inc << endl;
		}

		//Pause Fullscreen movie so the movie dont go out of sync
		obj.movie.pause();

		sfemov.movie->setPlayingOffset(time + sf::seconds(value.inc));

		//Moves forward in the smaller movie with 10 seconds
		if (mod.oneMovie->switchON)
		sfemov.movie2->setPlayingOffset(time + sf::seconds(value.inc) - sfm.off);

		obj.movie.play();
		break;

		///If user clicks the left arrow button
	case sf::Keyboard::Left:
		//gets the current playing time
		time = sf::seconds(sfemov.movie->getPlayingOffset().asSeconds());

		//Pause Fullscreen movie so the movie dont go out of sync
		obj.movie.pause();

		sfemov.movie->setPlayingOffset(time - sf::seconds(10));
		//Moves backwards in the smaller movie with 10 seconds
		if (mod.oneMovie->switchON)
		sfemov.movie2->setPlayingOffset(time - sf::seconds(10) - sfm.off);

		obj.movie.play();

		break;

	case sf::Keyboard::E:
		if (mod.oneMovie->switchON) {
			if (sfemov.movie2->getStatus() == sfe::Playing)
				sfemov.movie2->pause();
			else
				sfemov.movie2->play();
		}
		break;

	case sf::Keyboard::Q:
		if (sfemov.movie->getStatus() == sfe::Playing)
			sfemov.movie->pause();
		else
			sfemov.movie->play();
		break;

	case sf::Keyboard::R:
		obj.movie.pause();

		obj.actions.reSync(sfm.off);

		obj.movie.play();

		break;

	case sf::Keyboard::G:
		syncMovie();
		break;
	case sf::Keyboard::LAlt:
		if (!bools.behind)
			bools.behind = true;
		else
			bools.behind = false;
		break;

	case sf::Keyboard::J:
		sfemov.movie2->stop();
		syncMovie();
	default:
		break;
	}
}


inline void keyPress::syncMovie() {
	sfm.off = sfemov.movie->getPlayingOffset();
	cout << sfm.off.asSeconds() << endl;
	if (mod.oneMovie->switchON) {
		if (sfemov.movie2->getStatus() != sfe::Playing) {
			sfemov.movie2->play();
			bools.movie2Active = true;
		}
	}
}