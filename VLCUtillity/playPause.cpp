#include "stdafx.h"
#include "playPause.h"
#include "Settings.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <algorithm>
#include <boost\filesystem.hpp>

using namespace std;
using namespace GV;
// Destructor, closes the CreateProcess Handles
playPause::~playPause() {
	///If the windows has been opened
	if (canopen) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(pi2.hProcess);
		CloseHandle(pi2.hThread);
	}
}

///Creates the VLC player process
void playPause::startVLC() {

	ZeroMemory(&si, sizeof(si));   //Fills the STARTUPINFO of first VLC memory with zeros
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));   //Fills the PROCESS_INFORMATION of first VLC memory with zeros

	ZeroMemory(&si2, sizeof(si2));   //Fills the STARTUPINFO of second VLC memory with zeros
	si2.cb = sizeof(si2); 
	ZeroMemory(&pi2, sizeof(pi2));   //Fills the PROCESS_INFORMATION of second VLC memory with zeros

	again:   //If the path was not found or the file did not exist and the user clicks RETRY

	//Gets the path of VLC
	if (boost::filesystem::exists("path.txt")) {
		//Opens the path file, if it exists
		path.open("Path.txt", fstream::in);

		getline(path, VLCstr);   //Gets the first line, vlc.exe path
		getline(path, font);   //Gets the second line, font path 

		///If the user havent entered the the actual vlc.exe
		if (VLCstr.find(".exe") == string::npos) {
			VLCstr += "/vlc.exe";   //this adds it
		}

		///If the VLC path is valid
		if (boost::filesystem::exists(VLCstr)) {
			j = wstring(VLCstr.begin(), VLCstr.end());   //Convert the path to wstring
			vlc = j.c_str();   //And the convert it to a LPCWSTR
			canopen = true;
		}
		///If the VLC path does not exist
		else {
			path.close(); //Close the path.txt, so the user can change it without having to close the program
			//Open a error prompt, that the vlc player path does not exist
			msg = MessageBoxW(NULL, L"VLC player path does not exist.\nopen The path.txt and see if anything is wrong", L"PATH DOES NOT EXIST", MB_RETRYCANCEL);
			if (msg == 4)
				goto again;
		}
	}//If path.txt does exist END
	//If the path.txt does not exist
	else {
		path.close(); //Close the path
		path.open("Path.txt", fstream::out);   //Then open it in fstream::out mode, so it will be created
		path.close();   //And then close it so the user can change it
		//Creates a error prompt
		msg = MessageBoxW(NULL, L"Path.txt file does not exists\nIt has probably been deleted somehow\nit has been created now", L"FILE DOES NOT EXIST", MB_RETRYCANCEL);
		canopen = false;
		if(msg == 4)
		goto again;
	}//If the path.txt doesnt exist END

	if (canopen) {   //If path is fine, and everything is setup
		//Creates the first VLC player process
		CreateProcess(vlc, L"vlc.exe", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);   
		//Creates the second VLC player process
		CreateProcess(vlc, L"vlc.exe", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);
	}

	//Debounce
	Sleep(100);
}
///Function leftclick, emulates a leftclick
void playPause::leftclick() {
	key.type = INPUT_MOUSE;   //sets the INPUT var type to emulate a mouse

	key.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;   //Sets the key to click down the left mouse button
	SendInput(1, &key, sizeof(key));   //Sends it to windows input handler

	ZeroMemory(&key, sizeof(key));   //Zeros the memory
	key.type = INPUT_MOUSE;   //Just in case;
	key.mi.dwFlags = MOUSEEVENTF_LEFTUP;   //Sets the key to release the left mouse button
	SendInput(1, &key, sizeof(key));   //Sends it to windows input handler
}//LeftClick() ENDL

///Function Play, this plays/pauses the players
void playPause::Play(sf::RenderWindow &window) {
	GetCursorPos(&prePos);   //Gets the position of the mouse before user clicks
							 //Play/Pause, so it can be returned after the fact
	//If the switch is ON
	if(hideWindow)
	//////////////////////////////////////////////////////////////////////////////////
	/// If you dont have multiple screens and this program is above the players, 
	/// it will hide the program, so the players can be clicked
	//////////////////////////////////////////////////////////////////////////////////
	ShowWindow(window.getSystemHandle(), SW_HIDE);

	//First VLC player
	SetCursorPos(firstPos.x, firstPos.y);   //Moves the mouse to the "Set pos 1"
	//leftclick();   //Dont know why this is here but I will keep it.
	leftclick();   //left clicks
	key.type = INPUT_KEYBOARD;   //Sets the INPUT type to keyboard
	key.ki.wVk = VK_SPACE;   //Sets the Virtual key to SPACE
	//////////////////////////////////////////////////////////////////////////////////
	/// Then sends "SPACE" to windows input handle, it will play/pause any
	/// media player inc. VLC player
	//////////////////////////////////////////////////////////////////////////////////
	SendInput(1, &key, sizeof(key));

	//Second VLC player
	SetCursorPos(secondPos.x, secondPos.y);   //Moves the mouse to the "Set pos 2"
	leftclick(); //left clicks

	key.type = INPUT_KEYBOARD;   //Sets the INPUT type to keyboard
	key.ki.wVk = VK_SPACE;   //Sets the Virtual key to SPACE
	SendInput(1, &key, sizeof(key));   //And then sends it

	//If the switch is ON
	if(hideWindow)  
	ShowWindow(window.getSystemHandle(), SW_SHOW);   //Shows the window after all of the above mess

	Sleep(100);   //Debounce
	SetForegroundWindow(window.getSystemHandle());   //Brings the program to the top
	SetCursorPos(prePos.x, prePos.y);
}


void playPause::setCursorVar(string b) {
	//If the user clicks the set pos 1 button
	if (b == "set 1") {
		Sleep(1500);   //Timer
		GetCursorPos(&firstPos);   //save the cursor pos in a POINT variable
	}
	//If ther user clicks the set pos 2 buttons
	else if (b == "set 2") {
		Sleep(1500);   //Timer
		GetCursorPos(&secondPos);   //save the cursor pos in a POINT variable
	}
	//Saves the saved positions in the settings save file
	//Only if the saved positions isnt 0
	if (secondPos.x != 0 && secondPos.y != 0 && firstPos.x != 0 && firstPos.y != 0) {
		settings.open("Settings.txt", fstream::out);

		settings << firstPos.x << " " << firstPos.y
			<< " " << secondPos.x << " " << secondPos.y;

		settings.close();
	}
}
