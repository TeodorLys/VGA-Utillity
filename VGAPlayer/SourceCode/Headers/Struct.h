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
#include "Spacer.h"
#include "Debugging.h"
#include "MovieEvents.h"
#include "Themes.h"
#include "SaveAble.h"
#include "SaveSettings.h"
#include <sfeMovie\Movie.hpp>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <boost\filesystem.hpp>

struct sfemovie {
	sfe::Movie *movie = nullptr; 
	sfe::Movie *movie2 = nullptr; 
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
	Debugging debugs;
	Movies movie;
	Themes theme;
};

struct strings {
	std::string moviePath;
	std::string APTpath;
	std::string strTime;
	std::string smallstrTime;

	std::string movieSavePath;

	std::string limitList = "1234567890.-";   //Debug

	boost::filesystem::path current;

	std::fstream setting;
	std::fstream movieFile;
};

struct values {
	
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
	int initx;  //Initial mouse position X
	int inity;  //Initial mouse position Y
	int ok;
	float mov1SaveTime = 0;
	float mov2SaveTime = 0;
	float mov2OffsetTime = 0; 

	const int incBy = 5;
	const short uiIndex = 4;

	int mov1Vol = 0;   //fullscreen movie volume variable
	int mov2Vol = 0;   //Smaller movie volume variable
	float inc = 0;
	float w;
	float h;
	const float width = 1080;
	const float height = 720;
	float newWidth;
	float newHeight;
	float mx;   //Initial smaller movie position X
	float my;   //Initial smaller movie position Y
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
	bool endOfMovie = false;
	bool menuIsShown = true;
	bool beforeStart = false;
	bool movie2Greater;
	bool movie2Active = false;
};

struct modules {
	//Creates an play button object
	Buttons *play = new Buttons;
	//Creates an ffstv button object
	Buttons *ffstv = new Buttons;
	//Creates an film button object
	Buttons *film = new Buttons;

	//End screen when the movie(s) is over--
	Buttons *replay = new Buttons;
	Buttons *ret = new Buttons;
	//--//

	Switch *oneMovie = new Switch;

	textButton *about = new textButton;
	textButton *mainMovText = new textButton;

	ContextMenu *basic = new ContextMenu;
	ContextMenu *mainMovie = new ContextMenu;

	std::vector<ContextMenu*> allCM;

	Spacer *spacers = new Spacer;
};

struct sfml {
	sf::Event event;
	sf::Time off;
	sf::Font font;
	sf::Font sysFont;
	sf::Text OMov;
	sf::Text OVGA;
	sf::Text tPlay;
	sf::Text tTimer;
	sf::Text smalltTimer;
	sf::Text vol1;
	sf::Text vol2;
	sf::Sprite stest;
	sf::Texture te;
	sf::Texture base;
	sf::Texture ffsBG;
	sf::RectangleShape b;
	sf::RectangleShape theCrew;
	sf::Color COMov = sf::Color(255, 255, 255);
	sf::Color COVGA = sf::Color(255, 255, 255);
	sf::RenderWindow window;
	sf::Mouse mouse;
};

struct SaveAbleVariables {
	SaveSettings settings;
	SaveSettings saveMovies;
	SAInt volume1;
	SAInt volume2;
	SAFloat mov1Time;
	SAFloat mov2Time;
	SAFloat mov2Offset;
	SAString mov1Path;
	SAString mov2Path;
	SaveAbleVariables::SaveAbleVariables() : volume1("volume1", 0), 
											 volume2("volume2", 0),
											 mov1Time("mov1Time", 0),
											 mov2Time("mov2Time", 0),
											 mov2Offset("mov2Offset", 0),
											 mov1Path("mov1Path", "\\"),
											 mov2Path("mov2Path", "\\"){}
};
