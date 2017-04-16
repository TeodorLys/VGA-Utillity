#include "mouseEvent.h"
#include "GlobalVariables.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace GV;

void mouseEvent::mouseWheel(sf::Event event) {
	///IF mouse is over the smaller movie
	if (mod.oneMovie->switchON) {
		if (obj.actions.movie2Hover()) {
			///If the mouse wheel is moved, and if the variable is not over 100
			if (event.mouseWheel.delta > 0 && value.mov2Vol != 100 && bools.movieIsPlaying) {

				value.mov2Vol += value.incBy;

				//Increment volume with 1
				sfemov.movie2.setVolume((float)value.mov2Vol);

				//Changes the on screen text
				sfm.vol2.setString(to_string(value.mov2Vol));

			}
			//If mouse wheel is moved in the other direction
			else if (event.mouseWheel.delta < 0 && value.mov2Vol != 0 && bools.movieIsPlaying) {

				value.mov2Vol -= value.incBy;
				//Decrement volume with -1
				sfemov.movie2.setVolume((float)value.mov2Vol);

				sfm.vol2.setString(to_string(value.mov2Vol));
			}
		}
		//If mouse is over the "Fullscreen" movie
		else if (!obj.actions.movie2Hover()) {
			///The same as above but for the fullscreen movie...
			if (event.mouseWheel.delta > 0 && value.mov1Vol != 100 && bools.movieIsPlaying) {

				value.mov1Vol += value.incBy;

				sfemov.movie.setVolume((float)value.mov1Vol);

				sfm.vol1.setString(to_string(value.mov1Vol));
			}
			else if (event.mouseWheel.delta < 0 && value.mov1Vol != 0 && bools.movieIsPlaying) {

				value.mov1Vol -= value.incBy;

				sfemov.movie.setVolume((float)value.mov1Vol);

				sfm.vol1.setString(to_string(value.mov1Vol));
			}//Mouse wheel delta less END 
		}//If the mouse isnt over the smaller movie rectangle END
	}
	else {
		if (event.mouseWheel.delta > 0 && value.mov1Vol != 100 && bools.movieIsPlaying) {

			value.mov1Vol += value.incBy;

			sfemov.movie.setVolume((float)value.mov1Vol);

			sfm.vol1.setString(to_string(value.mov1Vol));
		}
		else if (event.mouseWheel.delta < 0 && value.mov1Vol != 0 && bools.movieIsPlaying) {

			value.mov1Vol -= value.incBy;

			sfemov.movie.setVolume((float)value.mov1Vol);

			sfm.vol1.setString(to_string(value.mov1Vol));
		}//Mouse wheel delta less END 
	}
}//mouseWheel Function END



////////////////////////////////////////////////////////////////////////////////////////////////
///Menu buttons events																		 ///																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::menuButtons() {
	///The below if statements can only be used if the movie isnt playing
	if (!bools.movieIsPlaying) {
		///Checks if the user has loaded the movies
		if (bools.canPlay) {
			///Checks if the mouse is over the PLAY buttons
			if (mod.play->Hover(sf::Color(175, 175, 175), 2)) {
				///Checks if the left mouse button is pressed
				if (obj.actions.Click() && !bools.doonce && !bools.mouseClick && bools.focus) {
					//Runs the start movies function
					startMovies();

					float buff = sfemov.movie.getDuration().asSeconds() / 60;
					value.hour = buff / 60;
					value.minute = buff - (value.hour * 60);
					value.second = sfemov.movie.getDuration().asSeconds() - (((value.hour * 60) * 60) + (value.minute * 60));
					
					if (mod.oneMovie->switchON) {
						buff = 0;

						buff = sfemov.movie2.getDuration().asSeconds() / 60;
						value.smallhour = buff / 60;
						value.smallminute = buff - (value.smallhour * 60);
						value.smallsecond = sfemov.movie2.getDuration().asSeconds() - (((value.smallhour * 60) * 60) + (value.smallminute * 60));

					
					}
					//Infinity blocker
					bools.doonce = true;
				}
			}
		}

		loadMovieButtons();
		emptyPath();

		if (!bools.switchOnce) {
			if (mod.oneMovie->clickSwitch()) {
				bools.switchOnce = true;
			}
		}
	}
}//menuButtons Function END

 ////////////////////////////////////////////////////////////////////////////////////////////////
 /// \Private help function to menuButtons													  ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::loadMovieButtons() {
	///Checks if the mouse is over the OPEN FFSTV VIDEO button
	if (mod.ffstv->Hover(sf::Color(175, 175, 175), 2)) {
		///Checks if the left mouse button is pressed
		if (obj.actions.Click() && !bools.doonce && !bools.mouseClick && bools.focus) {

			//Runs the Load Movie function, with an 1 as a parameter
			//to tell the function that I am loading the first movie
			obj.initial.LoadMovie(1);

			//Infinity blocker
			bools.doonce = true;
		}
	}

	if (mod.oneMovie->switchON) {
		mod.film->setButtonColor(sf::Color(0, 0, 0), sf::Color(255, 125, 0), 5.5f);
		mod.film->setTextColor(sf::Color(255, 125, 0));

		///Else check if the mouse is over the OPEN MOVIE FILE button
		if (mod.film->Hover(sf::Color(175, 175, 175), 2)) {
			///Checks if the left mouse button is pressed
			if (obj.actions.Click() && !bools.doonce && !bools.mouseClick && bools.focus) {

				//Loads the Load Movie function, with a 2 as a parameter
				//to tell the function that I am loading the second movie
				obj.initial.LoadMovie(2);

				//Infinity stone
				bools.doonce = true;
			}
		}
	}
	else if (!mod.oneMovie->switchON) {
		mod.film->setButtonColor(sf::Color(50, 50, 50), sf::Color(100, 65, 0), 5.5f);
		mod.film->setTextColor(sf::Color(100, 65, 0));
	}
}//LoadMovieButtons Function END


 ////////////////////////////////////////////////////////////////////////////////////////////////
 /// \Private help function to menuButtons 					   								  ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::emptyPath() {
	///Checks if the user has loaded some movies
	if (obj.initial.ffs != "NONE" && obj.initial.mov != "NONE" || obj.initial.ffs != "NONE" && !mod.oneMovie->switchON) {

		//If so change the play button colors to "ACTIVE"
		mod.play->setButtonColor(sf::Color(0, 0, 0), sf::Color(255, 125, 0), 5.5f);

		mod.play->setTextColor(sf::Color(255, 125, 0));

		//And tells the above if statement that it is ok to play the movie
		bools.canPlay = true;
	}
}//EmptyPath Function END

////////////////////////////////////////////////////////////////////////////////////////////////
///Checks if the mouse is still																 ///																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::checkUI(chrono::high_resolution_clock::time_point &tStart, chrono::high_resolution_clock::time_point &tEnd) {
	if (sfm.mouse.getPosition().x == value.mousePosX && sfm.mouse.getPosition().y == value.mousePosY && bools.isFullscreen) {
		if (chrono::duration_cast<chrono::milliseconds>(tStart - tEnd).count() >= 2000) {
			bools.mouseIsStill = true;
			bools.mouseOnce = true;
		}
	}
	else {
		bools.mouseIsStill = false;
		value.mousePosX = sfm.mouse.getPosition().x;
		value.mousePosY = sfm.mouse.getPosition().y;
		tEnd = chrono::high_resolution_clock::now();

	}

	showHideUI();

}//CheckUI Function END

////////////////////////////////////////////////////////////////////////////////////////////////
///When the mouse is still do this...														 ///																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::showHideUI() {
	if (!bools.mouseIsStill) {
		if (bools.mouseOnce) {
			sfm.window.setMouseCursorVisible(true);
			sfm.vol1.setFillColor(sf::Color(sfm.vol1.getFillColor().r, sfm.vol1.getFillColor().g, sfm.vol1.getFillColor().b, 255));
			sfm.vol2.setFillColor(sf::Color(sfm.vol2.getFillColor().r, sfm.vol2.getFillColor().g, sfm.vol2.getFillColor().b, 255));
			sfm.smalltTimer.setFillColor(sf::Color(sfm.smalltTimer.getFillColor().r, sfm.smalltTimer.getFillColor().g, sfm.smalltTimer.getFillColor().b, 255));
			sfm.tTimer.setFillColor(sf::Color(sfm.tTimer.getFillColor().r, sfm.tTimer.getFillColor().g, sfm.tTimer.getFillColor().b, 255));
			bools.mouseOnce = false;
		}
	}
	else {
		sfm.window.setMouseCursorVisible(false);
		sfm.vol1.setFillColor(sf::Color(sfm.vol1.getFillColor().r, sfm.vol1.getFillColor().g, sfm.vol1.getFillColor().b, 0));
		sfm.vol2.setFillColor(sf::Color(sfm.vol2.getFillColor().r, sfm.vol2.getFillColor().g, sfm.vol2.getFillColor().b, 0));
		sfm.smalltTimer.setFillColor(sf::Color(sfm.smalltTimer.getFillColor().r, sfm.smalltTimer.getFillColor().g, sfm.smalltTimer.getFillColor().b, 0));
		sfm.tTimer.setFillColor(sf::Color(sfm.tTimer.getFillColor().r, sfm.tTimer.getFillColor().g, sfm.tTimer.getFillColor().b, 0));

	}
}//ShowHideUI Function END
