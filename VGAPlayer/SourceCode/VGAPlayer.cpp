
#include "stdafx.h"
#include "InitialSetup.h"
#include "Actions.h"
#include "GlobalVariables.h"
#include "fanArt.h"
#include "Buttons.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else 
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#endif // _DEBUG

using namespace std;
using namespace GV;

//Function Prototyping 
void rendering(sf::RenderWindow *window);
void enterFullscreen(sf::RenderWindow &window);
void exitFullscreen(sf::RenderWindow &window);
void startMovies();
void threadStart();
void threadPause();
void setButtons(Buttons &b, float sX, float sY, string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY);

//Booleans
bool focus = true;   //If thw window has focus or not
bool doonce;   //Infinity blocker
bool behind = false;   //If the smaller movie should be hidden
bool movieIsPlaying = false;   //If the movie is active
bool border;   //If the mouse is on and has clicked on the border
bool m_border1;   //... dont really know why but they are used
bool m_border2;   //... dont really know why but they are used
bool moveMovie = false;   //If the smaller movis is being moved
bool isFullscreen = false;   //If the window is in BORDERLESS fullscreen 
bool windowClosed = false;   //If the window has called the "destructor" sort of
bool pause = true;   //Pause the thread
bool canPlay = false;   //If all movies have been loaded

//Integers
int initx;   //Initial mouse position X
int inity;  //Initial mouse position Y
int mx;   //Initial smaller movie position X
int my;   //Initial smaller movie position Y
int newOffsetx;   //New movie position X, *NOT IN USE*
int newOffsety;   //New movie position Y, *NOT IN USE*

//LONGS WIN API variable
LONG SavelStyle;
LONG SavelExStyle;

sf::RectangleShape shape;   //Smaller movie location checker

condition_variable cv;   //Thread lock
mutex m;   //Dont really know, havent learnt that yet...

int main() {

	initial.movieWindow();   //Runs the initial movie parameters
	initial.UI();   //*NOT IN USE*
	//fanArt f;
	//f.download();
	int mov1Vol = 0;   //fullscreen movie volume variable
	int mov2Vol = 0;   //Smaller movie volume variable
	sf::Time time;   //setPlayingOffset variable

	//Sets the initial size of the smaller movie rectangle
	shape.setSize(sf::Vector2f(w, h));
	//Hides the smaller movie rectangle
	shape.setFillColor(sf::Color(0, 0, 0, 0));

	//Creates an play button object
	Buttons *play = new Buttons;
	//Creates an ffstv button object
	Buttons *ffstv = new Buttons;
	//Creates an film button object
	Buttons *film = new Buttons;

	//Sets the PLAY Button settings
	setButtons(*play, 20, 20, "Play", sf::Color(50, 50, 50), 
		        sf::Color(100, 65, 0), 5.5f, sf::Color(100, 65, 0), 
		        sf::Vector2f(window.getSize().x / 2, window.getSize().y - 100), 2, 2);

	//Sets the OPEN FFSTV VIDEO settings
	setButtons(*ffstv, 20, 20, "Open FFSTV Video", sf::Color(0,0,0), 
		        sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0), 
		        sf::Vector2f(200, window.getSize().y - 100), 1, 1);

	//Sets the OPEN MOVIE FILE settings
	setButtons(*film, 20, 20, "Open Movie File", sf::Color(0,0,0),
		sf::Color(255, 125, 0) , 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f(window.getSize().x - 200, window.getSize().y - 100), 1, 1);

	//Launches the Draw thread
	window.setActive(false);
	//Sets up the thread
	thread render( bind(rendering, &window));

	initial.files();

	//Event handling
	while (window.isOpen()){
		///The below if statements can only be used if the movie isnt playing
		if (!movieIsPlaying) {
			///Checks if the user has loaded the movies
			if (canPlay) {
				///Checks if the mouse is over the PLAY buttons
				if (play->Hover(sf::Color(175, 175, 175), 2)) {
					///Checks if the left mouse button is pressed
					if (actions.Click() && !doonce) {
						//Runs the start movies function
						startMovies();
						//Infinity blocker
						doonce = true;
					}
				}
			}
			///Checks if the mouse is over the OPEN FFSTV VIDEO button
			if (ffstv->Hover(sf::Color(175, 175, 175), 2)) {
				///Checks if the left mouse button is pressed
				if (actions.Click() && !doonce) {
					//Runs the Load Movie function, with an 1 as a parameter
					//to tell the function that I am loading the first movie
					initial.LoadMovie(1);
					//Infinity blocker
					doonce = true;
				}
			}
			///Else check if the mouse is over the OPEN MOVIE FILE button
			else if (film->Hover(sf::Color(175, 175, 175), 2)) {
				///Checks if the left mouse button is pressed
				if (actions.Click() && !doonce) {
					//Loads the Load Movie function, with a 2 as a parameter
					//to tell the function that I am loading the second movie
					initial.LoadMovie(2);
					//Infinity stone
					doonce = true;
				}
			}

			///Checks if the user has loaded some movies
			if (initial.ffs != "NONE" && initial.mov != "NONE") {
				//If so change the play button colors to "ACTIVE"
				play->setButtonColor(sf::Color(0, 0, 0), sf::Color(255, 125, 0), 5.5f);
				play->setTextColor(sf::Color(255, 125, 0));
				//And tells the above if statement that it is ok to play the movie
				canPlay = true;
			}
		}

		//To make sure that I am not trying to access a NULL object
		if (movieIsPlaying) {
			///If the mouse is inside the smaller movie window
			if (mouse.getPosition(window).x > GV::movie2.getPosition().x &&
				mouse.getPosition(window).y > GV::movie2.getPosition().y && mouse.getPosition(window).y < movie.getPosition().y + (window.getSize().y / 2)) {
				//If so then check if left mouse button is pressed and the movie isnt being moved
				if (actions.Click() && !moveMovie) {
					//Saves the initial mouse X position
					initx = mouse.getPosition(window).x;
					//Saves the initial mouse Y position
					inity = mouse.getPosition(window).y;
					//Saves the initial movie X position
					mx = GV::movie2.getPosition().x;
					//Saves the initial Y position
					my = GV::movie2.getPosition().y;
					//Telling the if statement below that iam moving the movie
					moveMovie = true;
				}
			}
			//Checking with the if statement above
			if (moveMovie) {
				//Changes the movie position, with the previously saved parameters
				//and with the current mouse position 
				GV::movie2.setPosition(sf::Vector2f(mouse.getPosition(window).x + (mx - initx), mouse.getPosition(window).y + (my - inity)));
				//Updates the movie for some reason, why not...
				GV::movie2.update();
				//Saves the new position, but this didnt work
				newOffsetx = GV::movie2.getPosition().x;
				newOffsety = GV::movie2.getPosition().y;
			}

			///If the user Clicks the window border
			if (mouse.getPosition(window).x >= 0 && mouse.getPosition(window).y <= 0) {
				//If the left mouse button is pressed
				if (actions.Click() && !m_border1) {
					//Changes the OpenGL to false, mostly for the thread
					window.setActive(false);   
					//Starts the Thread
					threadStart();
					//Tells the if statement in the thread to Draw all the stuff
					border = true;
					m_border1 = true;   //Dont really know what these do...
					m_border2 = false; //...
				}
			}
			else {
				if (!m_border2) {
					//Pauses the thread, so the CPU dont get angry at me
					threadPause();
					//Tells the if statment in the thread to stop
					border = false;
					m_border2 = true;   //Same as before... dont really know...
					m_border1 = false;   //...
				}
			}//And here
		}
		///Checks if the user doesnt click the left mouse button
		if (!actions.Click()) {
			//If the movie has been moved
			if (moveMovie) {
				moveMovie = false;
			}
			//Resets the Doonce for buttons
			doonce = false;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			///Basically a destructor
			if (event.type == sf::Event::Closed) {
				windowClosed = true;   //Variable for the second thread
				Sleep(100);   //Dont really know why this exists but... here it is...
				render.detach();   //Detaches the thread so it can safely exit
				window.close();   //Close the SFML window
			}
			//Checks if the program has focus
			//So you cant click buttons when the program is underneath other programs
			else if (event.type == sf::Event::LostFocus) {
				focus = false;
			}
			//Checks if the program has focus
			else if (event.type == sf::Event::GainedFocus) {
				focus = true;
			}
			//Checks if the user clicks any buttons
			if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				///If the user clicks SPACE
				case sf::Keyboard::Space:
					//Checks if the movie is playing
					if (movie.getStatus() == sfe::Playing) {
						//Pauses the movies if it is playing
						movie.pause();
						 GV::movie2.pause();
					}
					else {
						//If the movie isnt playing, play them
						movie.play();
						 GV::movie2.play();
					}
					break;
					///If the user clicks the 'F' key
				case sf::Keyboard::F:
					///Not really functionall at the moment
					//Checks if the screen already is in fullscreen
					if (!isFullscreen) {
						//Runs the Enter Fullscreen function
						enterFullscreen(window);
						//Changes the variable
						isFullscreen = true;
					}
					else {
						//Runs the Exit Fullscreen function
						exitFullscreen(window);
						//Changes the variable
						isFullscreen = false;
					}
					break;
					///If the user clicks the right arrow button
				case sf::Keyboard::Right:
					//gets the current playing time
					time = sf::seconds(movie.getPlayingOffset().asSeconds());
					//Pause Fullscreen movie so the movie dont go out of sync
					movie.pause();
					 GV::movie2.pause();   //Pause smaller movie, sync problem...^
					 //Moves forward in the fullscreen movie with 10 seconds
					  movie.setPlayingOffset(time + sf::seconds(10));
					  //Moves forward in the smaller movie with 10 seconds
					   GV::movie2.setPlayingOffset(time + sf::seconds(10));
					      movie.play();   //Starts the movies again 
					       GV::movie2.play();   //Starts the movies again 
					break;
					///If user clicks the left arrow button
				case sf::Keyboard::Left:
					//gets the current playing time
					time = sf::seconds(movie.getPlayingOffset().asSeconds());
					//Pause Fullscreen movie so the movie dont go out of sync
					movie.pause();  
					 GV::movie2.pause();   //Pause smaller movie, sync problem...^
					 //Moves backwards in the fullscreen movie with 10 seconds
					  movie.setPlayingOffset(time - sf::seconds(10));
					  //Moves backwards in the smaller movie with 10 seconds
					   GV::movie2.setPlayingOffset(time - sf::seconds(10));
					    movie.play();   //Starts the movies again 
					     GV::movie2.play();    //Starts the movies again 
					break;
				default:
					break;
				}
			}
			else if (event.type == sf::Event::Resized) {
				//When the movie is playing
				if (movieIsPlaying) {
					//Fits the smaller movie the the resized window size
				     GV::movie2.fit(0, 0, window.getSize().x, window.getSize().y);
					 //Corrects for the resized window size
					  GV::movie2.setPosition(window.getSize().x / 2, movie.getPosition().y);
					  //This "Shape" is so you can change volume of the smaller movie
					  //And this corrects the size of that for the resized window
					   shape.setPosition(GV::movie2.getPosition().x, GV::movie2.getPosition().y);
					   //Corrects the size, for the changed window size
					  shape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
					  //Fits the "Fullscreen" movie for the resized window size
				 	 movie.fit(0, 0, window.getSize().x, window.getSize().y);
					 //Volume indicator for the resized window
					 vol2.setPosition(window.getSize().x - 60, 0);
				}
				else {
					//Size correction for the TEMP background
					ffssp[0].setSize(sf::Vector2f(window.getSize().x, window.getSize().x * 9 / 16));
					//Menu PLAY button Scaling
					play->ScreenScaleing(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 100), 2, 2);
					//"Loads Fullscreen movie button" Scaling
					ffstv->ScreenScaleing(sf::Vector2f(play->getNew() * 200 - 200, window.getSize().y - 100), 1, 1);
					//"Load the Smaller movie" button Scaling 
					film->ScreenScaleing(sf::Vector2f(window.getSize().x - (play->getNew() * 200 - 200), window.getSize().y - 100), 1, 1);
				}
				  //Sets the window view for the resized window, So it doesnt stretch
				 window.setView(sf::View(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y)));
			}

			//////////////////////////////////////////////////////////////////////////
			/// \Change volume of both movies									   ///
			/// If you hold the mouse over one movie you change the volume		   ///
			/// of only that movie                                                 ///
			//////////////////////////////////////////////////////////////////////////
			else if (event.type == sf::Event::MouseWheelMoved) {
				//IF mouse is over the smaller movie
				if (actions.Hover(shape)) {
					//If the mouse wheel is moved, and if the variable is not over 100
					if (event.mouseWheel.delta > 0 && mov2Vol != 100 && movieIsPlaying) {
						mov2Vol += 1;
						//Increment volume with 1
						GV::movie2.setVolume(mov2Vol);
						//Changes the on screen text
						vol2.setString(to_string(mov2Vol));
					}
					//If mouse wheel is moved in the other direction, and if 
					//the volume variable is not 0
					else if(event.mouseWheel.delta < 0 && mov2Vol != 0 && movieIsPlaying) {
						mov2Vol -= 1;
						//Decrement volume with -1
						GV::movie2.setVolume(mov2Vol);
						//Changes the on screen text
						vol2.setString(to_string(mov2Vol));
					}
				}
				//If mouse is over the "Fullscreen" movie
				else if (!actions.Hover(shape)) {
					//The same as above but for the fullscreen movie...
					if (event.mouseWheel.delta > 0 && mov1Vol != 100 && movieIsPlaying) {
						mov1Vol += 1;
						movie.setVolume(mov1Vol);
						vol1.setString(to_string(mov1Vol));
					}
					else if(event.mouseWheel.delta < 0 && mov1Vol != 0 && movieIsPlaying){
						mov1Vol -= 1;
						movie.setVolume(mov1Vol);
						vol1.setString(to_string(mov1Vol));
					}//Mouse wheel delta less END 
				}//If the mouse isnt over the smaller movie rectangle END
			}//Mouse wheel moved END 
		}//Poll event END
	
		///Menu
		if (!movieIsPlaying) {

			window.clear();   //Clears the RAM of all unused stuff /*I think*/

			window.draw(ffssp[0]);   //Draws the background
			play->draw();   //Draws the play button 
			ffstv->draw();   //Draws the OPEN FFSTV VIDEO button
			film->draw();   //Draws the OPEN MOVIE FILE button

			window.display();   //Display what was just drawn
		}
		///Movie play Locally
		else if(!border){

			movie.update();   //Updates the fullscreen movie
			GV::movie2.update();   //Updates the smaller movie
			
			window.clear();   //Clears the RAM
			
			window.draw(movie);   //Draws the newly updated fullscreen movie frame
			window.draw(GV::movie2);   //Draws the newly updated smaller movie frame
			
			window.draw(vol1);   //Draws the fullscreen movie volume text
			window.draw(vol2);   //Draws the smaller movie volume text
			
			window.display();   //And displays that
		}
	}
}

//This is a second thread, which means that the videos will play even though you move or resize the window
void rendering(sf::RenderWindow *window) {
	//Only runs while the SFML window is open
	while (window->isOpen()) {
		//If the movie is playing, if the mouse is on and clicked the border,
		//And the window isnt closed
		if (movieIsPlaying && border && !windowClosed) {
			
			movie.update();   //Update the fullscreen movie
			GV::movie2.update();   //Updates the smaller movie

			window->clear();   //Clears the RAM

			//Not in use at the moment, but
			//If the user what to hide the smaller movie
			if (!behind) {
				window->draw(movie);
				window->draw(GV::movie2);   //In front of the fullscreen movie
			}
			else {
				window->draw(GV::movie2);   //Behind the fullscreen movie
				window->draw(movie);
			}
			
			window->draw(vol1);   //Draws the fullscreen movie volume text
			window->draw(vol2);   //Draws the smaller movie volume text
			window->display();   //And displays that
		}
		//If the mouse isnt on and clicked the border
		else {
			window->setActive(false);   //Safety precaution 
			//If the main thread tells this thread to pause
			while (pause) {
				unique_lock<mutex> lk(m);
				cv.wait(lk);   //Waits for the main thread to tell otherwise
				lk.unlock();   //Unlocks the unique_lock
			}
		}
	}
}

///Sets the window in BORDERLESS fullscreen mode
///Doesnt really work at the moment but will fix it later
///I would otherwise had to destroy the SFML window
///And the create it again as fullscreen
void enterFullscreen(sf::RenderWindow &window) {
		LONG lStyle = GetWindowLong(window.getSystemHandle(), GWL_STYLE);
		SavelStyle = lStyle;
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
		SetWindowLong(window.getSystemHandle(), GWL_STYLE, lStyle);
		LONG lExStyle = GetWindowLong(window.getSystemHandle(), GWL_EXSTYLE);
		SavelExStyle = lExStyle;
		lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		SetWindowLong(window.getSystemHandle(), GWL_EXSTYLE, lExStyle);
		isFullscreen = true;
}


///Exits the BORDERLESS fullscreen 
void exitFullscreen(sf::RenderWindow &window) {
		SetWindowLong(window.getSystemHandle(), GWL_STYLE, SavelStyle);
		SetWindowLong(window.getSystemHandle(), GWL_EXSTYLE, SavelExStyle);
		isFullscreen = false;
}

///Runs all of the setup for the movies
void startMovies() {
	window.setActive(false);   //Safety precaution
	movieIsPlaying = true;   //Tells if statements that the movie is playing
	//Gets the current desktop mode / desktop resolution
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	//Chooses which is smallest, movie or screen,
	//and will scale the window accordingly
	w = min(static_cast<float>(desktopMode.width), movie.getSize().x);
	h = min(static_cast<float>(desktopMode.height), movie.getSize().y);

	//Absolute minimum
	if (w * h < 1.f) {
		w = max(w, 250.f);
		h = max(h, 40.f);
	}
	//Sets the scale of the smaller movie, so it is...smaller
	GV::movie2.setScale(window.getSize().x / (window.getSize().x * 2.f), window.getSize().y / (window.getSize().y * 2.f));
	//Then fits the movie to the window
	GV::movie2.fit(0, 0, w, h);
	//Plays the smaller movie
	GV::movie2.play();
	//Moves the smaller movie over so it is on the other side of the window
	GV::movie2.setPosition(w / 2, 0);

	//Fits the fullscreen movie to the window
	movie.fit(0, 0, w, h);
	//Plays the fullscreen movie
	movie.play();
	//Sets the initial volume, only for debug for now
	movie.setVolume(0);
	//Same with the smaller movie
	GV::movie2.setVolume(0);

	//Shape is so the program knows when the mouse is over the smaller movie
	//Initial scale of the smaller movie rectangle
	shape.setScale(GV::movie2.getScale().x, GV::movie2.getScale().y);
	//Initial position of that shape
	shape.setPosition(GV::movie2.getPosition().x, GV::movie2.getPosition().y);

	window.setSize(sf::Vector2u(w, h));   //Sets the size of the window accordingly
	//Stretch safety
	window.setView(sf::View(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y)));
	//Disables OpenGL
	window.setActive(false);
}

void threadStart() {
	lock_guard<mutex> lk(m);
	pause = false;   //Tells the thread to exit out of the while loop
	cv.notify_one();   //Notify the condition_variable on the second thread that
					   //it is ok to start
}

void threadPause() {
	lock_guard<mutex> lk(m);
	pause = true;   //Tells the thread to start the while loop
}

//Sets the initial Buttons variables
void setButtons(Buttons &b, float sX, float sY, string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY) {
	b.setSize(sX, sY);
	b.setText(text);
	b.setScale(sf::Vector2f(scaleX, scaleY));
	b.setButtonColor(c, out, outsize);
	b.setTextColor(tc);
	b.setPosition(p);
}
