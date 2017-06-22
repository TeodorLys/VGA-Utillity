//2017-05-1 19:26, Currently: 2384 lines of code
#include "stdafx.h"
#include "GlobalVariables.h"
#include "Buttons.h"
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")

using namespace std;
using namespace GV;

/*---(Function Prototype)---*/
void rendering(sf::RenderWindow *window);  //separate Thread
void threadStart();
void threadPause();
void localMenuRender();
void localMovieRender();

bool windowClosed = false;

std::condition_variable cv;   //Thread lock
std::mutex m;   //Dont really know, havent learnt that yet...

chrono::high_resolution_clock::time_point tStart;
chrono::high_resolution_clock::time_point tEnd;

int main() {
	
	GV::obj.initial.files();   //settings.txt
	GV::obj.initial.movieWindow();   //Runs the initial movie parameters

	sf::Time time;   //used for setPlayingOffset variable

	GV::obj.initial.menuButtonsSettings();   //Initializes all of the menu buttons
	GV::obj.re.menuResize();

	sfm.window.setActive(false); //For the seperate Thread(render)
	thread render(bind(rendering, &sfm.window));   //Sets up the thread

	mod.oneMovie->setBase();

	cout << sizeof(value) << endl;

	/*---(Runtime stuff)---*/
	while (sfm.window.isOpen()) {
		if (bools.movieIsPlaying && obj.debugs.convValue) {
			cout << obj.actions.movie2Hover() << " " << " | ";
			cout << floor(sfemov.movie2->getSize().x / sfemov.movie2->getSize().y) << " | ";
			cout << sfemov.movie2->getScale().x << " " << sfemov.movie2->getScale().y << " | ";
			cout << obj.debugs.convValue << " | ";
			cout << obj.actions.yLimit << " | ";
			cout << sfm.window.getSize().x << " " << sfm.window.getSize().y << " | ";
			cout << sfemov.movie->getSize().x << " " << sfemov.movie->getSize().y << endl;
		}

		GV::obj.me.menuButtons();  //Checks if user clicks any buttons	

		if(bools.endOfMovie)
			GV::obj.me.endScreen();

		//Starts the timer for to Hide the UI if the mouse is still for 2 seconds
		tStart = chrono::high_resolution_clock::now();

		//Cycle through all of the contextmenu
		for (int a = 0; a < 2; a++) {
			if (mod.allCM[a]->contextMenuShown) {
				GV::obj.me.showContextMenuSelector(*mod.allCM[a]);
			}
		}
		
		//When the switch is ON change the crew image black
		if (!mod.oneMovie->switchON) {
			sfm.theCrew.setFillColor(sf::Color(0, 0, 0, 150));
		}
		//Otherwise return to normal color
		else {
			sfm.theCrew.setFillColor(sf::Color(255,255,255, 255));
		}

	   //To make sure that users is not trying to access a NULL objeect
	   if (bools.movieIsPlaying) {
		   //And if oneMovie Switch is on(to only play one movie)
		   if (mod.oneMovie->switchON) {
			   //And if mouse is over the second movie
			   if (GV::obj.actions.movie2Hover()) {
				   //And if Mouse is clicked, and the second movie isnt being moved and mouse button isnt clicked
				   if (GV::obj.actions.Click() && !bools.moveMovie && !bools.mouseClick) {
					   value.initx = sfm.mouse.getPosition(sfm.window).x;
					   value.inity = sfm.mouse.getPosition(sfm.window).y;
					   value.mx = sfemov.movie2->getPosition().x;
					   value.my = sfemov.movie2->getPosition().y;

					   bools.moveMovie = true;
				   }
			   }
			   //Checking with the if statement above
			   if (bools.moveMovie) {
				   //Changes the movie position, with the previously saved parameters
				   //and with the current mouse position 
				   sfemov.movie2->setPosition(sf::Vector2f(sfm.mouse.getPosition(sfm.window).x + (value.mx - value.initx),
				   sfm.mouse.getPosition(sfm.window).y + (value.my - value.inity)));
			   }
		   }

			//If the user Clicks the window border, Start Thread
			if (sfm.mouse.getPosition(sfm.window).x >= 0 && sfm.mouse.getPosition(sfm.window).y <= 0) {
				//And the mouse is clicked, and hasent been clicked before(without releaseing mouse button)
				if (GV::obj.actions.Click() && !bools.m_border1 && !bools.mouseClick) {
					//Changes the OpenGL to false, mostly for the thread
					sfm.window.setActive(false);
					threadStart();

					//Tells the if statement in the thread to Draw all the stuff
					bools.border = true;
					bools.m_border1 = true;
					bools.m_border2 = false; 
				}
			}
			//If user doesnt click the border
			else {
				//And the border has been clicked before
				if (!bools.m_border2) {
					//Pauses the thread, so the CPU dont get angry at me
					threadPause();

					bools.border = false;
					bools.m_border2 = true;
					bools.m_border1 = false;  
				}
			}
		}
		else if (!bools.movieIsPlaying && bools.beforeStart) {
			bools.beforeStart = false;
		}

		while (sfm.window.pollEvent(sfm.event)) {
			switch (sfm.event.type) {
			case sf::Event::Closed:
				GV::obj.ev.SaveSettings();
				windowClosed = true;   //Variable for the second thread

				Sleep(100);

				render.detach();   //Detaches the thread so it can safely exit		
				sfm.window.close();   //Close the SFML window
				break;

			case sf::Event::LostFocus:
				bools.focus = false;
				break;

			case sf::Event::GainedFocus:
				bools.focus = true;
				break;

			default:
				break;
			}

			if (sfm.event.type == sf::Event::MouseButtonPressed) {
				GV::obj.me.contextMenuHandler();
			}

			if (obj.debugs.writing) {
				obj.debugs.valueField();
			}

			//Checks if the user clicks any buttons
			GV::obj.ev.checkKeypress(sfm.event, time);
		}//Poll event END
	
		 //If the mouse is only clicked and not on any button
		if (GV::obj.actions.Click()) {
			bools.mouseClick = true;
		}

		else if (!GV::obj.actions.Click()) {
			//If the movie has been moved
			if (bools.moveMovie)
				bools.moveMovie = false;

			//Resets the Doonce for buttons
			bools.doonce = false;
			bools.mouseClick = false;
			bools.switchOnce = false;
		}

		//Hide Context Menu if Window looses focus
		if (!bools.focus) {
			mod.basic->contextMenuShown = false;
			mod.basic->showSelector();

			mod.mainMovie->contextMenuShown = false;
			mod.mainMovie->showSelector();
		}

		obj.movie.movieTimers();

		GV::obj.me.checkUI(tStart, tEnd);

		if (!bools.menuIsShown && sfemov.movie->getPlayingOffset().asSeconds() >= sfemov.movie->getDuration().asSeconds()) {

			bools.endOfMovie = true;
			bools.movieIsPlaying = false;
			bools.movie2Active = false;

			sfm.window.clear(sf::Color(50,50,50));
			
			mod.ret->draw();
			mod.replay->draw();
			
			sfm.window.display();
		}

		///Menu
		if (!bools.movieIsPlaying && !bools.endOfMovie) {
			bools.menuIsShown = true;
			localMenuRender();
		}
			///Movie play Locally
		else if (!bools.border && !bools.endOfMovie) {
			bools.menuIsShown = false;
				localMovieRender();

				if (!bools.beforeStart) {
					//Need to reset the window, otherwise coordinates are weird.
					ShowWindow(sfm.window.getSystemHandle(), SW_RESTORE);
					ShowWindow(sfm.window.getSystemHandle(), SW_MAXIMIZE);
					bools.beforeStart = true;
				}
		}
	}//Draw END
}//Main Function END


/////////////////////////////////////////////////////////////
/// \Renders the menu objects							  ///
/////////////////////////////////////////////////////////////
void localMenuRender() {

	sfm.window.clear();   //Clears the RAM of all unused stuff /*I think*/

	sfm.window.draw(sfm.b);   //Draws the background
	sfm.window.draw(sfm.theCrew);
	mod.play->draw();   //Draws the play button 
	mod.ffstv->draw();   //Draws the OPEN FFSTV VIDEO button
	mod.film->draw();   //Draws the OPEN MOVIE FILE button

	mod.oneMovie->draw();

	if (mod.basic->contextMenuShown) {
		mod.basic->draw();
	}

	if (obj.debugs.writing)
		obj.debugs.draw();

	sfm.window.display();   //Display what was just drawn
}


/////////////////////////////////////////////////////////////
/// \Renders the movie(s) Locally                         ///
/////////////////////////////////////////////////////////////
void localMovieRender() {
	obj.movie.updateMovies(sfm.window, *sfemov.movie, *sfemov.movie2);

	sfm.window.clear();   //Clears the RAM

	if (!bools.behind) {
		obj.movie.drawMovieInv(sfm.window, *sfemov.movie, *sfemov.movie2);
	}
	else {
		obj.movie.drawMovie(sfm.window, *sfemov.movie, *sfemov.movie2);
	}

	obj.movie.drawVol(sfm.window, sfm.vol1, sfm.vol2);

	obj.movie.drawVol(sfm.window, sfm.tTimer, sfm.smalltTimer);

	if (mod.mainMovie->contextMenuShown) {
		mod.mainMovie->draw();
	}

	if (obj.debugs.writing)
		obj.debugs.draw();

	sfm.window.display();
}


/////////////////////////////////////////////////////////////
/// \This is a second thread, which means that the videos ///
/// \will play even though you move or resize the window  ///
/////////////////////////////////////////////////////////////
void rendering(sf::RenderWindow *window) {
	///Only runs while the SFML window is open
	while (window->isOpen()) {
		///If the movie is playing, if the mouse is on and clicked the border,
		///And the window isnt closed
		if (bools.movieIsPlaying && bools.border && !windowClosed) {
			
			obj.movie.updateMovies(*window, *sfemov.movie, *sfemov.movie2);

			window->clear();   //Clears the RAM

			///Not in use at the moment, but
			///If the user what to hide the smaller movie
			if (!bools.behind) {
				obj.movie.drawMovieInv(*window, *sfemov.movie, *sfemov.movie2);
			}
			else {
				obj.movie.drawMovie(*window, *sfemov.movie, *sfemov.movie2);
			}
			
			obj.movie.drawVol(*window, sfm.vol1, sfm.vol2);

			//window->draw(sfm.tTimer);

			//if (mod.oneMovie->switchON)
			//window->draw(sfm.smalltTimer);

			obj.movie.drawVol(*window, sfm.tTimer, sfm.smalltTimer);

			window->display();   //And displays that
		}
		//If the mouse isnt on and clicked the border
		else {
			window->setActive(false);   //Safety precaution 

			while (bools.pause) {
				unique_lock<mutex> lk(m);
				cv.wait(lk);   //Waits for the main thread to tell otherwise
				lk.unlock();   //Unlocks the unique_lock
			}
			window->setActive(false);
		}
	}
}

void threadStart() {
	lock_guard<mutex> lk(m);
	bools.pause = false;   //Tells the thread to exit out of the while loop
	cv.notify_one();   //Notify the condition_variable on the second thread that
					   //it is ok to start
}

void threadPause() {
	lock_guard<mutex> lk(m);
	bools.pause = true;   //Tells the thread to start the while loop
}