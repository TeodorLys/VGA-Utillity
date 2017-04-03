#pragma once

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <fstream>
#include <string>

class playPause
{
private:
	///First VLC player information 
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	///Second VLC player information 
	STARTUPINFO si2;
	PROCESS_INFORMATION pi2;

	///Enables the CreateProcess to fire if the path was found
	bool canopen = false;

	LPCWSTR vlc;   //The path of VLC player
	std::string VLCstr;   //Initial String
	std::wstring j;   //Converstion from string to wstring, that then can be converted to LPCWSTR

	INPUT key = { 0 };   //The keyboard/Mouse "SendInput"
	POINT prePos;   //Temporary mouse position save for when clicking play/pause

public:

	playPause();   //Constructor
	~playPause();   //Destructor
	void setCursorVar(std::string b);
	void Play(sf::RenderWindow &window);
	void leftclick();
	void startVLC();

};

