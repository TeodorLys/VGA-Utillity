#pragma once
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Color.hpp>
#include "InitialSetup.h"
#include "Actions.h"
#include "fanArt.h"
#include "Buttons.h"
#include "Resized.h"
#include "keyPress.h"
#include "mouseEvent.h"
#include "Events.h"
#include "movieDuration.h"
#include "Switch.h"
#include "ContextMenu.h"
#include "ContextMenuObjects.h"
#include <sfeMovie\Movie.hpp>
#include <Windows.h>
#include <boost\filesystem.hpp>

struct sfemovie {
	sfe::Movie movie;
	sfe::Movie movie2;
};

struct objects {
	InitialSetup initial;
	Actions actions;
	fanArt fa;
	Resized re;
	keyPress kp;
	mouseEvent me;
	Events ev;
	movieDuration md;
	//ContextMenu cm;
};

struct strings {
	std::string moviePath;
	std::string APTpath;
	std::string strTime;
	std::string smallstrTime;
	boost::filesystem::path current;
};

struct values {
	float mov1Vol = 0;   //fullscreen movie volume variable
	float mov2Vol = 0;   //Smaller movie volume variable
	int msg;
	int currentHour;
	int currentMinute;
	int currentSecond;
	int hour;
	int minute;
	int second;
	int smallcurrentHour;
	int smallcurrentMinute;
	int smallcurrentSecond;
	int smallhour;
	int smallminute;
	int smallsecond;
	int mousePosX = 0;
	int mousePosY = 0;
	int initx;   //Initial mouse position X
	int inity;  //Initial mouse position Y
	const int incBy = 5;
	const short uiIndex = 4;

	float w;
	float h;
	float width = 1080;
	float height = 720;
	float mx;   //Initial smaller movie position X
	float my;   //Initial smaller movie position Y
	
	LONG SavelStyle;
	LONG SavelExStyle;
};

struct booleans {

	bool canPlay = false;   //If all movies have been loaded
	bool doonce;   //Infinity blocker
	bool mouseClick = false;
	bool moveMovie = false;   //If the smaller movie is being moved
	bool movieIsPlaying = false;   //If the movie is active
	bool isFullscreen = false;   //If the window is in BORDERLESS fullscreen 
	bool border;   //If the mouse is on and has clicked on the border
	bool m_border1;
	bool m_border2;
	bool pause = true;   //Pause the thread
	bool focus = true;   //If the window has focus or not
	bool changeStyle = false;
	bool behind = false;   //If the smaller movie should be hidden
	bool mouseIsStill = false;
	bool mouseOnce = false;
	bool switchOnce = false;
	bool contextMenu = false;
};

struct modules {
	//Creates an play button object
	Buttons *play = new Buttons;
	//Creates an ffstv button object
	Buttons *ffstv = new Buttons;
	//Creates an film button object
	Buttons *film = new Buttons;

	Switch *oneMovie = new Switch;

	textButton *about = new textButton;

	ContextMenu *basic = new ContextMenu;
	ContextMenu *other = new ContextMenu;
};

struct sfml {
	sf::Time off;
	sf::Text vol1;
	sf::Text vol2;
	sf::Font font;
	sf::Font sysFont;
	sf::Text OMov;
	sf::Text OVGA;
	sf::Text tPlay;
	sf::Text tTimer;
	sf::Text smalltTimer;
	sf::Sprite stest;
	sf::Texture te;
	sf::Texture base;
	sf::RectangleShape b;
	sf::Color COMov = sf::Color(255, 255, 255);
	sf::Color COVGA = sf::Color(255, 255, 255);
	sf::Texture ffsBG;
	sf::RectangleShape theCrew;
	sf::RenderWindow window;
	sf::Mouse mouse;
};
