#include "stdafx.h"
#include "playPause.h"
#include "Turbo.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;
void setText(sf::Text &text, string t, sf::RectangleShape &shape, sf::Font &font, int x, int y, float size);
void setShape(sf::RectangleShape &shape, sf::RenderWindow &window,
	sf::Vector2f &vec, sf::Color &c, sf::Color &oc, int x, int y, int size, float outline);

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _DEBUG



const short sleepTime = 200;
bool doonce = false;
bool spritedoonce;
bool canClick = false;
bool ON = true;

int main() {

	sf::RenderWindow window(sf::VideoMode(400, 400), "Turbo", sf::Style::Close);

	window.setActive(false);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);

	const int playIndex = 6;
	const int textIndex = 6;
	sf::RectangleShape play[playIndex];
	sf::Text text[textIndex];
	sf::Font font;
	sf::Mouse mouse;
	sf::Image icon;

	turbo t;
	icon.create(32, 32, t.turboBuddy);
	playPause pp;

	window.setIcon(32, 32, icon.getPixelsPtr());

	string strplay = "Play/Pause";
	string setone = "Set Pos 1";
	string settwo = "Set Pos 2";
	string vlcstr = "START VLC";
	///Tries to load the font
	if (!font.loadFromFile("c:/windows/fonts/arial.ttf")) {
		int msg = MessageBox(NULL, L"Font could not be loaded", L"FONT WAS NOT FOUND", MB_OKCANCEL);
		cout << "could not load font" << endl;
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
	setText(text[0], strplay, play[0], font, 122, 30, 1.5f);  //PLAY PAUSE TEXT
	setText(text[1], setone, play[1], font, 70, 20, 1);   //SET POS 1 TEXT
	setText(text[2], settwo, play[2], font, 70, 20, 1);   //SET POS 2 TEXT
	setText(text[3], vlcstr, play[3], font, 90, 22, 1);   //START VLC TEXT 90 22
	setText(text[4], "ON", play[4], font, -10, -15, 0.6f);   //START VLC TEXT
	setText(text[5], "OFF", play[5], font, 25, 40, 0.6f);   //START VLC TEXT

	pp.SetupStuff();


	if (pp.hideWindow) {
		play[5].setPosition(play[4].getPosition().x + 12, play[4].getPosition().y);
		ON = false;
	}
	else {
		play[5].setPosition(play[4].getPosition().x - 12, play[4].getPosition().y);
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
				play[0].setFillColor(sf::Color(100, 50, 50));   //If hover over: Change color
				if (mouse.isButtonPressed(sf::Mouse::Left) && !spritedoonce && !canClick) {
					pp.Play(window);
					spritedoonce = true;   //Blocker so it doesnt fire infinitly
				}//If clicked END
			}//If button hover END
			else {
				play[0].setFillColor(sf::Color(200, 100, 100));
			}

			/////////////////////////////////////////////////////////////////////////////////
			/// \If the Set Pos 1 is hovered over and or clicked
			/// These buttons are for saving the cursor position for the pause of the 
			/// VLC players, just click the button and hold the mouse over the VLC
			/// window until the button changes back to "UNHOVERED" color
			/// and you are good to go
			//////////////////////////////////////////////////////////////////////////////////
			if (play[1].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[1].setFillColor(sf::Color(50, 50, 100));
				if (mouse.isButtonPressed(sf::Mouse::Left) && !spritedoonce && !canClick) {
					pp.setCursorVar("set 1");
					spritedoonce = true;
				}//If clicked END
			}//If button hover END
			else {
				play[1].setFillColor(sf::Color(100, 100, 200));   //Resets the color
			}

			/////////////////////////////////////////////////////////////////////////////////
			/// \If the Set Pos 2 is hovered over and or clicked
			/// These buttons are for saving the cursor position for the pause of the 
			/// VLC players, just click the button and hold the mouse over the VLC
			/// window until the button changes back to "UNHOVERED" color
			/// and you are good to go
			//////////////////////////////////////////////////////////////////////////////////
			if (play[2].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[2].setFillColor(sf::Color(50, 50, 100));   //If hovered over: Change color
				if (mouse.isButtonPressed(sf::Mouse::Left) && !spritedoonce && !canClick) {
					pp.setCursorVar("set 2");
					spritedoonce = true;
				}//If clicked END
			}//If button hover END
			else {
				play[2].setFillColor(sf::Color(100, 100, 200));
			}

			//////////////////////////////////////////////////////////////////////////////////
			/// \If the button START VLC is hovered over and or clicked
			/// And it will start VLC players for you (IF YOU WANT)
			//////////////////////////////////////////////////////////////////////////////////
			if (play[3].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
				play[3].setFillColor(sf::Color(57, 45, 27));   
				if (mouse.isButtonPressed(sf::Mouse::Left) && !spritedoonce && !canClick) {
					pp.startVLC();   //Sets up all of the process information and creates processes
					 spritedoonce = true;   
				}//If clicked END
			}//If button hover END

			///If cursor is not hovering over change back the color
			else {
				play[3].setFillColor(sf::Color(114, 91, 55));   //Change color
			}//Else button hover End

			//////////////////////////////////////////////////////////////////////////////////
			/// \If the switch is clicked
			/// Makes it so "ShowWindow((...), SW_HIDE)" wont fire
			//////////////////////////////////////////////////////////////////////////////////
			if (play[4].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window))) 
				&& mouse.isButtonPressed(sf::Mouse::Left) && !spritedoonce && !canClick) {
				if (ON) {
					play[5].setPosition(play[4].getPosition().x + 12, play[4].getPosition().y);
					pp.hideWindow = true;
					cout << pp.hideWindow << endl;
					ON = false;
				}
				else if (!ON) {
					play[5].setPosition(play[4].getPosition().x - 12, play[4].getPosition().y);
					pp.hideWindow = false;
					cout << pp.hideWindow << endl;
					ON = true;
				}
				spritedoonce = true;
			}

			///When the Left mouse button is released reset boolean
			if (!mouse.isButtonPressed(sf::Mouse::Left) && !canClick) {
				spritedoonce = false;
			}

		sf::Event event;
		while (window.pollEvent(event)) {

			
			if (event.type == sf::Event::LostFocus) {
				canClick = true;
			}
			else if (event.type == sf::Event::GainedFocus) {
				canClick = false;
			}

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(193, 164, 117));   //Sets the background Color
		for (int a = 0; a < playIndex; a++) {
			window.draw(play[a]);   //Draws the buttons
		}

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
}

///Sets the text
void setText(sf::Text &text, string t, sf::RectangleShape &shape, sf::Font &font, int x, int y, float size) {
	text.setString(t);
	text.setCharacterSize(sizeof(t));
	text.setScale(size, size);
	text.setPosition(shape.getPosition().x - x, shape.getPosition().y - y);
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color(0, 0, 0));
}
