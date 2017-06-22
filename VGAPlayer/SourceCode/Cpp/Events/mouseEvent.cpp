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
				 sfemov.movie2->setVolume(value.mov2Vol);
				  //Changes the on screen text
				  sfm.vol2.setString(to_string((int)value.mov2Vol));

			}
			//If mouse wheel is moved in the other direction
			else if (event.mouseWheel.delta < 0 && value.mov2Vol != 0 && bools.movieIsPlaying) {
				value.mov2Vol -= value.incBy;
				 //Decrement volume with -1
				 sfemov.movie2->setVolume(value.mov2Vol);
				  sfm.vol2.setString(to_string((int)value.mov2Vol));
			}
		}
		//If mouse is over the "Fullscreen" movie
		else if (!obj.actions.movie2Hover()) {
			///The same as above but for the fullscreen movie...
			if (event.mouseWheel.delta > 0 && value.mov1Vol != 100 && bools.movieIsPlaying) {
				value.mov1Vol += value.incBy;
				 sfemov.movie->setVolume(value.mov1Vol);
				  sfm.vol1.setString(to_string((int)value.mov1Vol));
			}
			else if (event.mouseWheel.delta < 0 && value.mov1Vol != 0 && bools.movieIsPlaying) {
				cout << value.mov1Vol << endl;
				value.mov1Vol -= value.incBy;
				 sfemov.movie->setVolume(value.mov1Vol);
				  sfm.vol1.setString(to_string((int)value.mov1Vol));
			}//Mouse wheel delta less END 
		}//If the mouse isnt over the smaller movie rectangle END
	}
	else {
		if (event.mouseWheel.delta > 0 && value.mov1Vol != 100 && bools.movieIsPlaying) {
			value.mov1Vol += value.incBy;
			 sfemov.movie->setVolume(value.mov1Vol);
			  sfm.vol1.setString(to_string((int)value.mov1Vol));
		}
		else if (event.mouseWheel.delta < 0 && value.mov1Vol != 0 && bools.movieIsPlaying) {
			value.mov1Vol -= value.incBy;
			 sfemov.movie->setVolume(value.mov1Vol);
			  sfm.vol1.setString(to_string((int)value.mov1Vol));
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

					float buff = sfemov.movie->getDuration().asSeconds() / 60;   //In minutes for easy convertion to hours and seconds
					value.hour = (int)buff / 60;   //Convertion from minute to hour
					value.minute = (int)buff - (value.hour * 60);   //Minutes are based on hour(even though hour is based on minutes)
																	//because if the movie is 1 hour and 10 min, if minutes isnt based on hours it would
																	//be 1 hour and 70 min.
					//Seconds are based on the entire duration of movies(in seconds) minus hour and minutes converted to seconds
					value.second = (int)sfemov.movie->getDuration().asSeconds() - (((value.hour * 60) * 60) + (value.minute * 60));
					
					if (mod.oneMovie->switchON) {
						buff = 0;
						//Same as above for the second movie
						buff = sfemov.movie2->getDuration().asSeconds() / 60;
						value.smallhour = (int)buff / 60;
						value.smallminute = (int)buff - (value.smallhour * 60);
						value.smallsecond = (int)sfemov.movie2->getDuration().asSeconds() - (((value.smallhour * 60) * 60) + (value.smallminute * 60));
					}
					//Infinity blocker
					bools.doonce = true;
				}//Mouse click END
			}//Mouse hover over play button END
		}//Movie is not playing END

		loadMovieButtons();
		emptyPath();

		if (!bools.switchOnce) {
			if (mod.oneMovie->clickSwitch()) {
				bools.switchOnce = true;
			}
		}
	}
}//menuButtons Function END

void mouseEvent::contextMenuSetup() {
	mod.basic->setup();
	mod.basic->addObject(*mod.about, "About");
	mod.basic->addObject(*mod.about, "DEBUG");
	mod.basic->objectsSetup();


	mod.mainMovie->setup();
	mod.mainMovie->addObject(*mod.mainMovText, "Play");
	mod.mainMovie->addObject(*mod.mainMovText, "Pause");
	mod.mainMovie->addObject(*mod.mainMovText, "Stop");
	mod.mainMovie->addObject(*mod.spacers, SPACER);
	mod.mainMovie->addObject(*mod.mainMovText, "DEBUG");
	mod.mainMovie->addObject(*mod.spacers, SPACER);
	mod.mainMovie->addObject(*mod.mainMovText, "Return");
	mod.mainMovie->addObject(*mod.mainMovText, "Replay");
	mod.mainMovie->addObject(*mod.mainMovText, "About");
	mod.mainMovie->objectsSetup();
	
	mod.allCM.push_back(mod.basic);
	mod.allCM.push_back(mod.mainMovie);

}//ContextMenuSetup Function END

void mouseEvent::showContextMenu(ContextMenu &cM) {
	if (sfm.mouse.isButtonPressed(sf::Mouse::Right) && bools.focus) {
		cM.setPosition();
		cM.contextMenuShown = true;
	}
	else if(!cM.isOver()){
		cM.contextMenuShown = false;
	}
}//ShowContextMenu Function END

void mouseEvent::showContextMenuSelector(ContextMenu &cM) {
	if (cM.showSelector()) {
		contextMenuDoEvents(cM);
	}
}//ShowContextMenuSelector Function END


 ////////////////////////////////////////////////////////////////////////////////////////////////
 /// \Handles all of the context menu clicks and										      ///
 /// \When certain menus should be shown							                          ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::contextMenuHandler() {
	if (bools.movieIsPlaying) {
		mod.basic->contextMenuShown = false;
		obj.me.showContextMenu(*mod.mainMovie);
	}
	else {
		mod.mainMovie->contextMenuShown = false;
		obj.me.showContextMenu(*mod.basic);
	}
}//ContextMenuHandler Function END


 ////////////////////////////////////////////////////////////////////////////////////////////////
 /// \Private help function to menuButtons													  ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
inline void mouseEvent::loadMovieButtons() {
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
		mod.film->setButtonColor(5.5f);
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
		mod.film->baseColor = sf::Color(50, 50, 50);
		mod.film->outLine = sf::Color(100,65,0),
		mod.film->setButtonColor(5.5f);
		mod.film->setTextColor(sf::Color(100, 65, 0));
	}
}//LoadMovieButtons Function END


 ////////////////////////////////////////////////////////////////////////////////////////////////
 /// \Private help function to menuButtons 					   								  ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
inline void mouseEvent::emptyPath() {
	///Checks if the user has loaded some movies
	if (obj.initial.ffs != "NONE" && obj.initial.mov != "NONE" || obj.initial.ffs != "NONE" && !mod.oneMovie->switchON) {

		//If so change the play button colors to "ACTIVE"
		mod.play->baseColor = sf::Color(0, 0, 0);
		mod.play->outLine = sf::Color(255, 125, 0);

		mod.play->setButtonColor(5.5f);

		mod.play->setTextColor(sf::Color(255, 125, 0));

		//And tells the above if statement that it is ok to play the movie
		bools.canPlay = true;
	}
}//EmptyPath Function END


////////////////////////////////////////////////////////////////////////////////////////////////
///Checks if the mouse is still, and are in Fullscreen mode 								 ///																			 
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
///When the mouse is still, Show/Hide UI    												 ///																			 
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


 ////////////////////////////////////////////////////////////////////////////////////////////////
 ///When the movie(s) end, so you can restart movie(s) or return to menu   					  ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::endScreen() {
	if (mod.replay->Hover(sf::Color(175,175,175), 2)) {
		if (obj.actions.Click() && !bools.doonce) {
			ReplayMovies();
		}
	}
	else if (mod.ret->Hover(sf::Color(175, 175, 175), 2)) {
		if (obj.actions.Click() && !bools.doonce) {
			ReturnToMenu();
		}
	}
	else {
	}
}//EndScreen Function END


 ////////////////////////////////////////////////////////////////////////////////////////////////
 ///If the users click replay movies														  ///																			 
 ////////////////////////////////////////////////////////////////////////////////////////////////
inline void mouseEvent::ReplayMovies() {
	obj.movie.stop();

	bools.endOfMovie = false;
	bools.movieIsPlaying = true;
	sfemov.movie->play();

	bools.doonce = true;
}


////////////////////////////////////////////////////////////////////////////////////////////////
///If the user click return to menu         												 ///																			 
////////////////////////////////////////////////////////////////////////////////////////////////
inline void mouseEvent::ReturnToMenu() {
	obj.movie.stop();
	
	bools.menuIsShown = true;
	bools.endOfMovie = false;
	bools.movieIsPlaying = false;
	bools.doonce = true;
}

void mouseEvent::contextMenuDoEvents(ContextMenu &cM) {
	if (obj.actions.Hover(cM.objects[cM.GetIndex("About")].textRect) && obj.actions.Click() && !bools.mouseClick) {
		value.msg = MessageBox(NULL, L"VGA Player ALPHA v0.1\nmade by Teodor", L"About VGA Player", MB_OK);
		bools.mouseClick = true;
	}
	else if (obj.actions.Hover(cM.objects[cM.GetIndex("Return")].textRect) && obj.actions.Click() && !bools.mouseClick) {
		ReturnToMenu();
		bools.mouseClick = true;
	}
	else if (obj.actions.Hover(cM.objects[cM.GetIndex("Replay")].textRect) && obj.actions.Click() && !bools.mouseClick) {
		ReplayMovies();
		bools.mouseClick = true;
	}
	else if (obj.actions.Hover(cM.objects[cM.GetIndex("DEBUG")].textRect) && obj.actions.Click() && !bools.mouseClick) {
		obj.debugs.bg.setPosition(sf::Vector2f((float)sfm.mouse.getPosition(sfm.window).x, (float)sfm.mouse.getPosition().y));
		obj.debugs.write.setPosition(sf::Vector2f(obj.debugs.bg.getPosition().x, obj.debugs.bg.getPosition().y));
		obj.debugs.writing = true;
		bools.mouseClick = true;
	}
}