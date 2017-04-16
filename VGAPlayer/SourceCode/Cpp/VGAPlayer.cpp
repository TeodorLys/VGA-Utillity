
#include "stdafx.h"
#include "GlobalVariables.h"
#include "Buttons.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;
using namespace GV;

//Function Prototyping 
void rendering(sf::RenderWindow *window);  //separate Thread
void threadStart();
void threadPause();
void setButtons(Buttons &b, float sX, float sY, string text, 
	            sf::Color &c, sf::Color &out, float outsize, 
	            sf::Color &tc, sf::Vector2f &p, float scaleX, 
	            float scaleY, float extra);

void localMenuRender();
void localMovieRender();
void setSwitches(Switch &s, float size, sf::Vector2f pos);

//Booleans
bool windowClosed = false;

std::condition_variable cv;   //Thread lock
std::mutex m;   //Dont really know, havent learnt that yet...

chrono::high_resolution_clock::time_point tStart;
chrono::high_resolution_clock::time_point tEnd;

int main() {

	obj.initial.files();

	obj.initial.movieWindow();   //Runs the initial movie parameters

	//obj.initial.UI();   //*NOT IN USE YET* 
	sf::Time time;   //setPlayingOffset variable

	//Sets the PLAY Button settings
	setButtons(*mod.play, 20, 20, "Play", sf::Color(50, 50, 50),
		sf::Color(100, 65, 0), 5.5f, sf::Color(100, 65, 0),
		sf::Vector2f(sfm.window.getSize().x / 2.f, sfm.window.getSize().y - 100.f), 2, 2, 7);

	//Sets the OPEN FFSTV VIDEO settings
	setButtons(*mod.ffstv, 20, 20, "Open FFSTV Video", sf::Color(0, 0, 0),
		sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f(200.f, sfm.window.getSize().y - 100.f), 1, 1, 5);

	//Sets the OPEN MOVIE FILE settings
	setButtons(*mod.film, 20, 20, "Open Movie File", sf::Color(0, 0, 0),
		sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f(sfm.window.getSize().x - 200.f, sfm.window.getSize().y - 100.f), 1, 1, 5);

	setSwitches(*mod.oneMovie, 5, sf::Vector2f(mod.play->getPosition().x, mod.play->getPosition().y - (mod.play->getSize().y)));

	sfm.window.setActive(false);

	//Sets up the thread
	thread render(bind(rendering, &sfm.window));

	mod.oneMovie->setBase();

	//Event handling
	while (sfm.window.isOpen()) {

		obj.me.menuButtons();  //Checks if user clicks any buttons

		//Starts the timer for to Hide the UI if the mouse is still for 2 seconds
		tStart = chrono::high_resolution_clock::now();

		if (!mod.oneMovie->switchON) {
			sfm.theCrew.setFillColor(sf::Color(0, 0, 0, 150));
		}
		else {
			sfm.theCrew.setFillColor(sf::Color(255,255,255, 255));
		}

		///To make sure that users is not trying to access a NULL object
		if (bools.movieIsPlaying) {
			if (mod.oneMovie->switchON) {
				if (obj.actions.movie2Hover()) {
					if (obj.actions.Click() && !bools.moveMovie && !bools.mouseClick) {
						//Saves the initial mouse X position
						value.initx = sfm.mouse.getPosition(sfm.window).x;
						//Saves the initial mouse Y position
						value.inity = sfm.mouse.getPosition(sfm.window).y;
						//Saves the initial movie X position
						value.mx = sfemov.movie2.getPosition().x;
						//Saves the initial Y position
						value.my = sfemov.movie2.getPosition().y;

						bools.moveMovie = true;
					}
				}
				///Checking with the if statement above
				if (bools.moveMovie) {
					//Changes the movie position, with the previously saved parameters
					//and with the current mouse position 
					sfemov.movie2.setPosition(sf::Vector2f(sfm.mouse.getPosition(sfm.window).x + (value.mx - value.initx), sfm.mouse.getPosition(sfm.window).y + (value.my - value.inity)));
					//Updates the movie so it continues playing while moving
					sfemov.movie2.update();
				}
			}

			///If the user Clicks the window border
			if (sfm.mouse.getPosition(sfm.window).x >= 0 && sfm.mouse.getPosition(sfm.window).y <= 0) {
				if (obj.actions.Click() && !bools.m_border1 && !bools.mouseClick) {
					//Changes the OpenGL to false, mostly for the thread
					sfm.window.setActive(false);

					//Starts the Thread
					threadStart();

					//Tells the if statement in the thread to Draw all the stuff
					bools.border = true;
					bools.m_border1 = true;
					bools.m_border2 = false; 
				}
			}
			else {
				if (!bools.m_border2) {
					//Pauses the thread, so the CPU dont get angry at me
					threadPause();
					//Tells the if statement in the thread to stop
					bools.border = false;
					bools.m_border2 = true;
					bools.m_border1 = false;  
				}
			}
		}
		//If the mouse is only clicked and not on any button
		if (obj.actions.Click()) {
			bools.mouseClick = true;
		}

		///Checks if the user doesnt click the left mouse button
		if (!obj.actions.Click()) {
			///If the movie has been moved
			if (bools.moveMovie) {
				bools.moveMovie = false;
			}
			//Resets the Doonce for buttons
			bools.doonce = false;
			bools.mouseClick = false;
			bools.switchOnce = false;
		}

		sf::Event event;
		while (sfm.window.pollEvent(event)) {

			///Basically a destructor
			if (event.type == sf::Event::Closed) {
				obj.ev.SaveSettings();

				windowClosed = true;   //Variable for the second thread
				
				Sleep(100);

				render.detach();   //Detaches the thread so it can safely exit
				
				sfm.window.close();   //Close the SFML window
			}

			//Checks if the program has focus
			//So you cant click buttons when the program is underneath other programs
			else if (event.type == sf::Event::LostFocus) {
				bools.focus = false;
			}
			else if (event.type == sf::Event::GainedFocus) {
				bools.focus = true;
			}

			///Checks if the user clicks any buttons
			obj.ev.checkKeypress(event, time);

		}//Poll event END

		obj.md.Timer();

		if (mod.oneMovie->switchON) 
			obj.md.smallTimer();

		obj.me.checkUI(tStart, tEnd);


		///Menu
		if (!bools.movieIsPlaying) {
			localMenuRender();
		}
			///Movie play Locally
		else if (!bools.border) {
			localMovieRender();

		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
/// \Renders the menu Objects
///////////////////////////////////////////////////////////////////////////////////////////
void localMenuRender() {

	sfm.window.clear();   //Clears the RAM of all unused stuff /*I think*/

	sfm.window.draw(sfm.b);   //Draws the background
	sfm.window.draw(sfm.theCrew);
	mod.play->draw();   //Draws the play button 
	mod.ffstv->draw();   //Draws the OPEN FFSTV VIDEO button
	mod.film->draw();   //Draws the OPEN MOVIE FILE button

	mod.oneMovie->draw();

	sfm.window.display();   //Display what was just drawn
}

///////////////////////////////////////////////////////////////////////////////////////////
/// \Renders the movie(s) Locally
///////////////////////////////////////////////////////////////////////////////////////////
void localMovieRender() {
	sfemov.movie.update();   //Updates the fullscreen movie

	if (mod.oneMovie->switchON)
		sfemov.movie2.update();   //Updates the smaller movie

	sfm.window.clear();   //Clears the RAM

	if (!bools.behind) {
		sfm.window.draw(sfemov.movie);   //Draws the newly updated fullscreen movie frame

		if (mod.oneMovie->switchON)
			sfm.window.draw(sfemov.movie2);   //Draws the newly updated smaller movie frame
	}
	else {

		if (mod.oneMovie->switchON)
			sfm.window.draw(sfemov.movie2);   //Draws the newly updated smaller movie frame

		sfm.window.draw(sfemov.movie);   //Draws the newly updated fullscreen movie frame
	}
	sfm.window.draw(sfm.vol1);   //Draws the fullscreen movie volume text

	if (mod.oneMovie->switchON)
		sfm.window.draw(sfm.vol2);   //Draws the smaller movie volume text

	sfm.window.draw(sfm.tTimer);

	if (mod.oneMovie->switchON)
		sfm.window.draw(sfm.smalltTimer);

	sfm.window.display();   //And displays that
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///This is a second thread, which means that the videos will play even though you move or resize the window ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rendering(sf::RenderWindow *window) {
	///Only runs while the SFML window is open
	while (window->isOpen()) {
		///If the movie is playing, if the mouse is on and clicked the border,
		///And the window isnt closed
		if (bools.movieIsPlaying && bools.border && !windowClosed) {
			
			sfemov.movie.update();   //Update the fullscreen movie

			if(mod.oneMovie->switchON)
			sfemov.movie2.update();   //Updates the smaller movie

			window->clear();   //Clears the RAM

			///Not in use at the moment, but
			///If the user what to hide the smaller movie
			if (!bools.behind) {
				window->draw(sfemov.movie);

				if (mod.oneMovie->switchON)
				window->draw(sfemov.movie2);   //In front of the fullscreen movie
			}
			else {
				if (mod.oneMovie->switchON)
				window->draw(sfemov.movie2); //Behind the fullscreen movie

				window->draw(sfemov.movie);
			}
			
			window->draw(sfm.vol1);   //Draws the fullscreen movie volume text
			if (mod.oneMovie->switchON)
			window->draw(sfm.vol2);   //Draws the smaller movie volume text

			window->draw(sfm.tTimer);

			if (mod.oneMovie->switchON)
			window->draw(sfm.smalltTimer);

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

//Sets the initial Buttons variables
void setButtons(Buttons &b, float sX, float sY, string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY, float extra) {
	b.setSize(sX, sY);
	b.setText(text);
	b.setScale(sf::Vector2f(scaleX, scaleY));
	b.setButtonColor(c, out, outsize);
	b.setTextColor(tc);
	b.setPosition(p, extra);
}

void setSwitches(Switch &s, float size, sf::Vector2f pos) {
	s.setBase();
	s.setScale(sf::Vector2f(size, size));
	s.setPosition(sf::Vector2f(pos));
}
