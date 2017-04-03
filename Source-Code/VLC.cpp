#include "stdafx.h"
#include "playPause.h"
#include "Turbo.h"
#include "Settings.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;
using namespace GV;

//Function Prototyping
void setText(sf::Text &text, string t, sf::RectangleShape &shape, sf::Font &font, int x, int y, float size);
void setShape(sf::RectangleShape &shape, sf::RenderWindow &window,
	sf::Vector2f &vec, sf::Color &c, sf::Color &oc, int x, int y, int size, float outline);

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _DEBUG

bool buttonDoonce;   //So if you click a button, it wont fire until you letgo of mouse
bool canClick = true;   //If the program is "out of Focus" you cant click the buttons
						 //If this did not exist you could click the buttons even if the program 
						 //is behind other programs
bool ON = true;   //The switch boolean

int main() {

	sf::RenderWindow window(sf::VideoMode(400, 400), "VGA Utillity", sf::Style::Close);

	window.setActive(false);   //Disable the OpenGL
	window.setFramerateLimit(60);   //Limits the framerate, so it doesnt use an unresonable amount of CPU
	window.setVerticalSyncEnabled(false);   //Disables the VSync, because nothing is moving...

	const int playIndex = 6;   //How many buttons there are
	const int textIndex = 7;   //How many individual text "blocks" there are
	sf::RectangleShape play[playIndex];   //Buttons Array
	sf::Text text[textIndex];   //Text Array
	sf::Font font;   //Font, Default Arial.ttf
	sf::Mouse mouse;   //Mouse object
	sf::Image icon;   //The program icon, see Turbo.h, it is in code(AWESOME!)

	turbo t;   //Icon class
	icon.create(32, 32, t.turboBuddy);   //Creates the turbobuddy from the Uint8 array
	
	playPause pp;   //playPause object
	Settings settings;   //Settings object

	window.setIcon(32, 32, icon.getPixelsPtr());   //Sets the newly created icon

	settings.SetupStuff();   //Runs the start up function

	///Tries to load the font
	if (!font.loadFromFile(GV::font)) {
		//If it failes, open a error window, because the console is off.
		int msg = MessageBox(NULL, L"Font could not be loaded", L"FONT WAS NOT FOUND", MB_OKCANCEL);
		//If the user hits CANCEL, exit program
		if (msg == 2) {
			return 0;
		}
	}

	///Shapes/Buttons
	//PLAY/PAUSE BUTTON
	setShape(play[0], window, sf::Vector2f(15, 8), sf::Color(200, 100, 100),
			 sf::Color(200, 75, 75), window.getSize().x / 2, window.getSize().y / 2 + 100, 20, 0.5f);   
	
	//SET POS 1 BUTTON
	setShape(play[1], window, sf::Vector2f(17, 8), sf::Color(100, 100, 200),
			 sf::Color(75, 75, 175), window.getSize().x / 4 + 10, window.getSize().y / 4 + 50, 10, 0.5f);   

    //SET POS 2 BUTTON
	setShape(play[2], window, sf::Vector2f(17, 8), sf::Color(114, 100, 200),
		     sf::Color(75, 75, 175), window.getSize().x / 4 + 195, window.getSize().y / 4 + 50, 10, 0.5f); 
    
	//START VLC BUTTON
	setShape(play[3], window, sf::Vector2f(20, 6), sf::Color(114, 91, 55),
		     sf::Color(94, 64, 35), window.getSize().x / 2, window.getSize().y / 4 - 50, 10, 0.5f); 

	//SWITCH BASE
	setShape(play[4], window, sf::Vector2f(13, 7), sf::Color(25, 25, 25),
			 sf::Color(100,100,100), 40, 50, 4, 1.0f);  
	//SWITCH
	setShape(play[5], window, sf::Vector2f(6, 6), sf::Color(150, 150, 150),
			 sf::Color(160, 160, 160), play[4].getPosition().x - 12, play[4].getPosition().y, 4, 0.2f);   

    ///TEXT
	setText(text[0], "Play/Pause", play[0], font, 0, 30, 1.5f);  //PLAY PAUSE TEXT
	setText(text[1], "Set Pos 1", play[1], font, 0, 22, 1);   //SET POS 1 TEXT
	setText(text[2], "Set Pos 2", play[2], font, 0, 22, 1);   //SET POS 2 TEXT
	setText(text[3], "START VLC", play[3], font, 0, 22, 1);   //START VLC TEXT
	setText(text[4], "ON", play[4], font, -20, -15, 0.6f);   //START VLC TEXT
	setText(text[5], "OFF", play[5], font, 0, 40, 0.6f);   //START VLC TEXT

	//Gets the saved state of the hideWindow switch
	if (hideWindow) {  //If, when the program was closed, the switch was ON
		play[5].setPosition(play[4].getPosition().x + 12, play[4].getPosition().y); //Change the position of switch
		ON = false;
	}
	else {   //If it was OFF
		play[5].setPosition(play[4].getPosition().x - 12, play[4].getPosition().y); //Change the position of switch
		ON = true;
	}


	while (window.isOpen()) {

			//////////////////////////////////////////////////////////////////////////////////
			/// \If the button START VLC is hovered over and or clicked
			/// When this button is pressed it will, change the mouse position,
			/// left click, and then press "SPACE", and then do the same for the other 
			/// VLC window. Because this was the only, SORT OF
			/// way of playing and pausing two VLC players at the exact same time
			//////////////////////////////////////////////////////////////////////////////////
			if (play[0].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[0].setFillColor(sf::Color(100, 50, 50));   //If hover over: Play/Pause, Change color
				//If play/pause is clicked
				if (mouse.isButtonPressed(sf::Mouse::Left) && !buttonDoonce && canClick) {
					pp.Play(window);
					buttonDoonce = true;   //Blocker so it doesnt fire infinitly
				}//If clicked END
			}//If button hover END
			else {
				play[0].setFillColor(sf::Color(200, 100, 100));   //Resets the color to original
			}//Else button is hover END

			/////////////////////////////////////////////////////////////////////////////////
			/// \If the Set Pos 1 is hovered over and or clicked
			/// These buttons are for saving the cursor position for the pause of the 
			/// VLC players, just click the button and hold the mouse over the VLC
			/// window until the button changes back to "UNHOVERED" color
			/// and you are good to go
			//////////////////////////////////////////////////////////////////////////////////
			if (play[1].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[1].setFillColor(sf::Color(50, 50, 100));   //If hover over: Set pos 1, Change color
				//If Set pos 1 is clicked
				if (mouse.isButtonPressed(sf::Mouse::Left) && !buttonDoonce && canClick) {
					pp.setCursorVar("set 1");   //Saves the position of the mouse
					buttonDoonce = true;
				}//If clicked END
			}//If button hover END
			else {
				play[1].setFillColor(sf::Color(100, 100, 200));   //Resets the color to original
			}//Else button is hover END

			/////////////////////////////////////////////////////////////////////////////////
			/// \If the Set Pos 2 is hovered over and or clicked
			/// These buttons are for saving the cursor position for the pause of the 
			/// VLC players, just click the button and hold the mouse over the VLC
			/// window until the button changes back to "UNHOVERED" color
			/// and you are good to go
			//////////////////////////////////////////////////////////////////////////////////
			if (play[2].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[2].setFillColor(sf::Color(50, 50, 100));   //If hovered over: Set pos 2, Change color
				//If Set pos 2 is clicked
				if (mouse.isButtonPressed(sf::Mouse::Left) && !buttonDoonce && canClick) {
					pp.setCursorVar("set 2");
					buttonDoonce = true;
				}//If clicked END
			}//If button hover END
			else {
				play[2].setFillColor(sf::Color(100, 100, 200));   //Resets the color to original
			}//Else button is hover END

			//////////////////////////////////////////////////////////////////////////////////
			/// \If the button START VLC is hovered over and or clicked
			/// And it will start VLC players for you (IF YOU WANT)
			//////////////////////////////////////////////////////////////////////////////////
			if (play[3].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[3].setFillColor(sf::Color(57, 45, 27));   //If hovered over: START VLC, Change color
				if (mouse.isButtonPressed(sf::Mouse::Left) && !buttonDoonce && canClick) {
					pp.startVLC();   //Sets up all of the process information and creates processes
					 buttonDoonce = true;   
				}//If clicked END
			}//If button hover END

			///If cursor is not hovering over change back the color
			else {
				play[3].setFillColor(sf::Color(114, 91, 55));   //Resets the color to original
			}//Else button hover End

			//////////////////////////////////////////////////////////////////////////////////
			/// \If the switch is clicked
			/// Makes it so "ShowWindow((...), SW_HIDE)" wont fire
			//////////////////////////////////////////////////////////////////////////////////
			if (play[4].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window))) 
				&& mouse.isButtonPressed(sf::Mouse::Left) && !buttonDoonce && canClick) {
				//If switch is ON
				if (ON) {
					//Change Position
					play[5].setPosition(play[4].getPosition().x + 12, play[4].getPosition().y);
					hideWindow = true;   //This variable is what is checked in playPause.cpp
					ON = false;
				}
				//If switch is not ON i.e. OFF
				else if (!ON) {
					//Change Posotion
					play[5].setPosition(play[4].getPosition().x - 12, play[4].getPosition().y);
					hideWindow = false;
					ON = true;
				}
				buttonDoonce = true;
			}//If switch is clicked END

			///When the Left mouse button is released reset boolean
			if (!mouse.isButtonPressed(sf::Mouse::Left) && canClick) {
				buttonDoonce = false;
			}

		sf::Event event;
		while (window.pollEvent(event)) {

			///When the window has lost ::LostFocus, you can click on the buttons
			if (event.type == sf::Event::LostFocus) {
				canClick = false;
			}
			///When the window has ::GainedFocus, you can click on the buttons
			else if (event.type == sf::Event::GainedFocus) {
				canClick = true;
			}
			///When the window is closed, close window...weird...
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(193, 164, 117));   //Sets the background Color
		//Cycle through buttons
		for (int a = 0; a < playIndex; a++) {
			window.draw(play[a]);   //Draws the buttons
		}
		//Cycles through Text
		for (int a = 0; a < textIndex; a++) {
			window.draw(text[a]);   //Draws the text
		}

		window.display();
	
	}//While window is open END
}//Function Main END

/// Sets all settings for the Shapes/Buttons
void setShape(sf::RectangleShape &shape, sf::RenderWindow &window, sf::Vector2f &vec, sf::Color &c, sf::Color &oc, int x, int y, int size, float outline) {
	shape.setSize(vec);
	shape.setFillColor(c);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setScale(size, size);
	shape.setPosition(x, y);
	shape.setOutlineColor(sf::Color(oc));
	shape.setOutlineThickness(outline);
}//Function SetShape END

///Sets the text
void setText(sf::Text &text, string t, sf::RectangleShape &shape, sf::Font &font, int x, int y, float size) {
	text.setString(t);
	text.setCharacterSize(sizeof(t));
	text.setScale(size, size);
	text.setPosition(shape.getPosition().x - x, shape.getPosition().y - y);
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color(0, 0, 0));
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, 0);
}//Function SetText END
