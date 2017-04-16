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
		if (sfemov.movie.getStatus() == sfe::Playing) {

			//Pauses the movies if it is playing
			sfemov.movie.pause();

			if (mod.oneMovie->switchON)
			sfemov.movie2.pause();
		}
		else {
			//If the movie isnt playing, play them
			sfemov.movie.play();

			if (mod.oneMovie->switchON)
			sfemov.movie2.play();
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
		time = sf::seconds(sfemov.movie.getPlayingOffset().asSeconds());

		//Pause Fullscreen movie so the movie dont go out of sync
		sfemov.movie.pause();

		if (mod.oneMovie->switchON)
		sfemov.movie2.pause();   //Pause smaller movie, sync problem...^
								 //Moves forward in the fullscreen movie with 10 seconds

		sfemov.movie.setPlayingOffset(time + sf::seconds(10));

		//Moves forward in the smaller movie with 10 seconds
		if (mod.oneMovie->switchON)
		sfemov.movie2.setPlayingOffset(time + sf::seconds(10) - sfm.off);

		sfemov.movie.play();

		if (mod.oneMovie->switchON)
		sfemov.movie2.play();
		break;

		///If user clicks the left arrow button
	case sf::Keyboard::Left:
		//gets the current playing time
		time = sf::seconds(sfemov.movie.getPlayingOffset().asSeconds());

		//Pause Fullscreen movie so the movie dont go out of sync
		sfemov.movie.pause();
		if (mod.oneMovie->switchON)
		sfemov.movie2.pause();   //Pause smaller movie, sync problem...^
								 //Moves backwards in the fullscreen movie with 10 seconds
		sfemov.movie.setPlayingOffset(time - sf::seconds(10));
		//Moves backwards in the smaller movie with 10 seconds
		if (mod.oneMovie->switchON)
		sfemov.movie2.setPlayingOffset(time - sf::seconds(10) - sfm.off);

		sfemov.movie.play();

		if (mod.oneMovie->switchON)
		sfemov.movie2.play();
		break;

	case sf::Keyboard::Q:
		if (mod.oneMovie->switchON) {
			if (sfemov.movie2.getStatus() == sfe::Playing)
				sfemov.movie2.pause();
			else
				sfemov.movie2.play();
		}
		break;

	case sf::Keyboard::E:
		if (sfemov.movie.getStatus() == sfe::Playing)
			sfemov.movie.pause();
		else
			sfemov.movie.play();
		break;

	case sf::Keyboard::R:
		sfemov.movie.pause();

		if (mod.oneMovie->switchON)
		sfemov.movie2.pause();

		obj.actions.reSync(sfm.off);

		sfemov.movie.play();

		if (mod.oneMovie->switchON)
		sfemov.movie2.play();
		break;

	case sf::Keyboard::G:
		sfm.off = sfemov.movie.getPlayingOffset();

		if (mod.oneMovie->switchON) {
			if (sfemov.movie2.getStatus() != sfe::Playing)
				sfemov.movie2.play();
		}
		break;
	case sf::Keyboard::LAlt:
		if (!bools.behind)
			bools.behind = true;
		else
			bools.behind = false;
		break;

	default:
		break;
	}
}
