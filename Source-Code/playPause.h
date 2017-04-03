#pragma once

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <fstream>
#include <string>

class playPause
{
private:

	HWND vlctwo = NULL;

	///First VLC player information 
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	///Second VLC player information 
	STARTUPINFO si2;
	PROCESS_INFORMATION pi2;

	///Open/Creates the path.txt file, that includes the path of VLC player
	std::fstream path;
	///Enables the CreateProcess to fire if the path was found
	bool canopen = false;
	LPCWSTR vlc;

	std::string h;
	std::wstring j;

	INPUT key = { 0 };
	POINT prePos;
	POINT firstPos;
	POINT secondPos;
	DWORD pid;
	std::fstream settings;
	int pidw;
	int pi2dw;
	const short sleepTime = 200;
public:
	bool hideWindow;
	playPause();
	~playPause();
	void setCursorVar(std::string b);
	void Play(sf::RenderWindow &window);
	void leftclick();
	void SetupStuff();
	void startVLC();

};

