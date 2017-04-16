#include "Events.h"
#include "GlobalVariables.h"
#include "Resized.h"
#include "keyPress.h"
#include <sfeMovie\Movie.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <boost\filesystem.hpp>

using namespace std;
using namespace GV;

void Events::checkKeypress(sf::Event event, sf::Time time) {
	if (event.type == sf::Event::KeyPressed) {
		obj.kp.press(event, time);
	}
	//Resize
	else if (event.type == sf::Event::Resized || bools.changeStyle) {
		///When the movie is playing
		if (bools.movieIsPlaying) {
			obj.re.playResize();
		}
		else {
			obj.re.menuResize();
		}

		//Sets the window view for the resized window, So it doesnt stretch
		sfm.window.setView(sf::View(sf::FloatRect(0, 0, (float)sfm.window.getSize().x, (float)sfm.window.getSize().y)));
		bools.changeStyle = false;
	}

	//////////////////////////////////////////////////////////////////////////
	/// \Change volume of both movies									   ///
	/// If you hold the mouse over one movie you change the volume		   ///
	/// of only that movie                                                 ///
	//////////////////////////////////////////////////////////////////////////
	else if (event.type == sf::Event::MouseWheelMoved) {
		obj.me.mouseWheel(event);
	}//Mouse wheel moved END 
}//Poll event END


///Sets the window in BORDERLESS fullscreen mode
void Events::enterFullscreen(sf::RenderWindow &window) {
	value.width = window.getSize().x;
	value.height = window.getSize().y;
	window.create(sf::VideoMode(value.w, value.h), "VGAPlayer", sf::Style::Fullscreen);
	bools.isFullscreen = true;
	bools.changeStyle = true;
}

///Exits the BORDERLESS fullscreen 
void Events::exitFullscreen(sf::RenderWindow &window) {
	window.create(sf::VideoMode(value.width, value.height), "VGAPlayer", sf::Style::Close | sf::Style::Resize);
	bools.isFullscreen = false;
	bools.changeStyle = true;
}

///Runs all of the setup for the movies
void Events::startMovies() {
	sfm.window.setActive(false);   //Safety precaution

	bools.movieIsPlaying = true;   //Tells if statements that the movie is playing
								   //Gets the current desktop mode / desktop resolution

	//Sets the scale of the smaller movie, so it is...smaller
	if (mod.oneMovie->switchON)
	sfemov.movie2.setScale(sfm.window.getSize().x / (sfm.window.getSize().x * 2.f), sfm.window.getSize().y / (sfm.window.getSize().y * 2.f));

	//Then fits the movie to the window
	if (mod.oneMovie->switchON)
	sfemov.movie2.fit(0, 0, value.w, value.h);

	//Moves the smaller movie over so it is on the other side of the window
	if (mod.oneMovie->switchON)
	sfemov.movie2.setPosition(value.w / 2, 0);

	//Fits the fullscreen movie to the window
	sfemov.movie.fit(0, 0, value.w, value.h);

	//Plays the fullscreen movie
	sfemov.movie.play();

	//Sets the initial volume, only for debug for now
	sfemov.movie.setVolume(value.mov1Vol);

	//Same with the smaller movie
	if (mod.oneMovie->switchON)
	sfemov.movie2.setVolume(value.mov2Vol);

	sfm.window.setSize(sf::Vector2u((unsigned int)value.w, (unsigned int)value.h));   //Sets the size of the window accordingly

	//Stretch safety
	sfm.window.setView(sf::View(sf::FloatRect(0, 0, (float)sfm.window.getSize().x, (float)sfm.window.getSize().y)));
	sfm.vol2.setPosition(sfm.window.getSize().x - 60.f, 25);

	sfm.tTimer.setPosition(0, sfm.window.getSize().y - sfm.tTimer.getGlobalBounds().height);
	if(mod.oneMovie->switchON)
	sfm.smalltTimer.setPosition(sfm.window.getSize().x - sfm.smalltTimer.getGlobalBounds().width, 
		                        sfm.window.getSize().y - sfm.smalltTimer.getGlobalBounds().height);

	//Disables OpenGL
	sfm.window.setActive(false);

}//startMovies Funtion END

void Events::SaveSettings() {
	fstream save;
	string p = str.current.string() + "\\Settings.txt";

	save.open(p, ios::out);
	if (save.is_open()) {
		save << "volume1: " << to_string(value.mov1Vol) << endl;
		save << "volume2: " << to_string(value.mov2Vol);
	}
	save.close();
}
