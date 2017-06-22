#include "Events.h"
#include "GlobalVariables.h"
#include "Resized.h"
#include "keyPress.h"
#include <sfeMovie\Movie.hpp>
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
		obj.initial.Movie2Limits();
		bools.changeStyle = false;
	}

	//////////////////////////////////////////////////////////////////////////
	/// \Change volume of both movies									   ///
	/// If you hold the mouse over one movie you change the volume		   ///
	/// of only that movie                                                 ///
	//////////////////////////////////////////////////////////////////////////
	else if (event.type == sf::Event::MouseWheelMoved) {
		if(bools.movieIsPlaying)
		obj.me.mouseWheel(event);
	}//Mouse wheel moved END 
}//Poll event END


///Sets the window in BORDERLESS fullscreen mode
void Events::enterFullscreen(sf::RenderWindow &window) {
	value.newWidth = (float)window.getSize().x;
	value.newHeight = (float)window.getSize().y;
	ShowWindow(sfm.window.getSystemHandle(), SW_MAXIMIZE);
	window.create(sf::VideoMode((unsigned int)value.w, (unsigned int)value.h), "VGAPlayer", sf::Style::None);
	bools.isFullscreen = true;
	bools.changeStyle = true;
}

///Exits the BORDERLESS fullscreen 
void Events::exitFullscreen(sf::RenderWindow &window) {
	window.create(sf::VideoMode((unsigned int)value.newWidth, (unsigned int)value.newHeight), "VGAPlayer", sf::Style::Close | sf::Style::Resize);
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
	sfemov.movie2->setScale(sfm.window.getSize().x / (sfm.window.getSize().x * 2.f), sfm.window.getSize().y / (sfm.window.getSize().y * 2.f));

	//Then fits the movie to the window
	if (mod.oneMovie->switchON)
	sfemov.movie2->fit(0, 0, value.w, value.h);

	//Moves the smaller movie over so it is on the other side of the window
	if (mod.oneMovie->switchON)
	sfemov.movie2->setPosition(value.w / 2, 0);

	//Fits the fullscreen movie to the window
	sfemov.movie->fit(0, 0, value.w, value.h);

	//Plays the fullscreen movie
	sfemov.movie->play();

	sfm.window.setSize(sf::Vector2u((unsigned int)value.w, (unsigned int)value.h));   //Sets the size of the window accordingly

	//Stretch safety
	sfm.window.setView(sf::View(sf::FloatRect(0, 0, (float)sfm.window.getSize().x, (float)sfm.window.getSize().y)));
	sfm.vol2.setPosition(sfm.window.getSize().x - 60.f, 25);

	sfm.tTimer.setPosition(0, sfm.window.getSize().y - sfm.tTimer.getGlobalBounds().height);
	if(mod.oneMovie->switchON)
	sfm.smalltTimer.setPosition(sfm.window.getSize().x - sfm.smalltTimer.getGlobalBounds().width, 
		                        sfm.window.getSize().y - sfm.smalltTimer.getGlobalBounds().height);

	obj.re.playMenuResize();

	//Disables OpenGL
	sfm.window.setActive(false);
	
	cout << value.mov1Vol << endl;
	cout << value.mov2Vol << endl;

	sfm.vol1.setString(to_string((int)value.mov1Vol));
	sfm.vol2.setString(to_string((int)value.mov2Vol));

	obj.movie.setVolume();

	obj.movie.setMovieTimes();

	if (value.mov2SaveTime != 0)
		sfemov.movie2->play();

}//startMovies Funtion END

void Events::SaveSettings() {
	string p = str.current.string() + "/config\\Settings.ini";
	ofstream t;
	str.setting.open(p, ios::out);
	if (str.setting.is_open()) {
		save.volume1.setV(ceil(sfemov.movie->getVolume()));
		save.volume2.setV(ceil(sfemov.movie2->getVolume()));

		save.settings.saveVariable(save.volume1, str.setting);
		save.settings.saveVariable(save.volume2, str.setting);
	}
	str.setting.close();

	p = str.movieSavePath;

	str.movieFile.open(p, ios::out);
	if (str.movieFile.is_open()) {
		save.mov1Time.setV(sfemov.movie->getPlayingOffset().asSeconds());
		save.mov2Time.setV(sfemov.movie2->getPlayingOffset().asSeconds());
		save.mov2Offset.setV(sfm.off.asSeconds());
		save.mov1Path.setV(obj.initial.ffs);
		save.mov2Path.setV(obj.initial.mov);

		save.saveMovies.saveVariable(save.mov1Time, str.movieFile);
		save.saveMovies.saveVariable(save.mov2Time, str.movieFile);
		save.saveMovies.saveVariable(save.mov2Offset, str.movieFile);
		save.saveMovies.saveVariable(save.mov1Path, str.movieFile);
		save.saveMovies.saveVariable(save.mov2Path, str.movieFile);
	}
	str.movieFile.close();
	p = str.current.string() + "\\config\\hash.vga";
	t.open(p);
	if (t.is_open()) {
		for (int a = 0; a < obj.initial.allHash.size(); a++) {
			t << obj.initial.allHash[a] << endl;
		}
	}
	t.close();
}