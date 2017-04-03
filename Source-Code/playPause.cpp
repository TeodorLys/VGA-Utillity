#include "stdafx.h"
#include "playPause.h"
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

HWND vlcone = NULL;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
playPause::playPause(){
}


playPause::~playPause() {

	settings.open("Settings.txt", fstream::out);
	settings << firstPos.x << " " << firstPos.y
		<< " " << secondPos.x << " " << secondPos.y << endl;;
	
	if (hideWindow) {
		settings << "true" << endl;
	}
	else {
		settings << "false" << endl;
	}

	if (canopen) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(pi2.hProcess);
		CloseHandle(pi2.hThread);
	}
}

void playPause::SetupStuff() {
	string b;
	settings.open("Settings.txt", fstream::in);
	if (settings.is_open()) {
		while (settings >> firstPos.x >> firstPos.y >> secondPos.x >> secondPos.y >> b);
		settings.close();
	}

	if (b == "true") {
		hideWindow = true;
	}
	else if(b == ""){
		hideWindow = false;
	}

}

void playPause::startVLC() {

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	ZeroMemory(&si2, sizeof(si2));
	si2.cb = sizeof(si2);
	ZeroMemory(&pi2, sizeof(pi2));

	again:
	path.open("Path.txt", fstream::in);

	getline(path, h);

	//Gets the path of VLC
	if (boost::filesystem::exists("path.txt")) {

		if (h.find(".exe") == string::npos) {
			h += "/vlc.exe";
		}
		if (boost::filesystem::exists(h)) {
			j = wstring(h.begin(), h.end());
			vlc = j.c_str();
			canopen = true;
		}
		else {
			path.close();
			int msg = MessageBoxW(NULL, L"VLC player path does not exist.\nopen The path.txt and see if anything is wrong", L"PATH DOES NOT EXIST", MB_RETRYCANCEL);
			if (msg == 4)
				goto again;
		}
	}
	else {
		path.close();
		path.open("Path.txt", fstream::out);
		path.close();
		int msg = MessageBoxW(NULL, L"Path.txt file does not exists\nit will not though just write the\nVLC path in there", L"FILE DOES NOT EXIST", MB_RETRYCANCEL);
		cout << "could not open file" << endl;
		canopen = false;
		if(msg == 4)
		goto again;
	}   //End find path

	if (canopen) {
		CreateProcess(vlc, L"vlc.exe", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		CreateProcess(vlc, L"vlc.exe", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);
	}


	Sleep(100);
	return;

	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);
	//CloseHandle(pi2.hProcess);
	//CloseHandle(pi2.hThread);
}

void playPause::leftclick() {
	key.type = INPUT_MOUSE;

	key.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &key, sizeof(key));

	ZeroMemory(&key, sizeof(key));
	key.type = INPUT_MOUSE;
	key.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &key, sizeof(key));

}

void playPause::Play(sf::RenderWindow &window) {

	GetCursorPos(&prePos);
	if(hideWindow)
	ShowWindow(window.getSystemHandle(), SW_HIDE);

	//First VLC player
	SetCursorPos(firstPos.x, firstPos.y);
	leftclick();
	leftclick();

	key.type = INPUT_KEYBOARD;
	key.ki.wVk = VK_SPACE;
	SendInput(1, &key, sizeof(key));

	//Second vlc player
	SetCursorPos(secondPos.x, secondPos.y);
	leftclick();
	key.type = INPUT_KEYBOARD;
	key.ki.wVk = VK_SPACE;

	SendInput(1, &key, sizeof(key));
	if(hideWindow)
	ShowWindow(window.getSystemHandle(), SW_SHOW);

	Sleep(100);
	SetForegroundWindow(window.getSystemHandle());
	SetCursorPos(prePos.x, prePos.y);
}

void playPause::setCursorVar(string b) {
	if (b == "set 1") {
		cout << "Hold cursor over First window" << endl;
		cout << "in";
		for (int b = 1; b < 4; b++) {
			for (int a = 1; a < 4; a++) {
				Sleep(sleepTime);
				cout << ".";
			}
			cout << b;
		}
		GetCursorPos(&firstPos);
		cout << "*camera click*" << endl;
		cout << "There DONE" << endl;
	}
	else if (b == "set 2") {
		cout << "Ok and now the second window" << endl;
		cout << "in";
		for (int b = 1; b < 4; b++) {
			for (int a = 1; a < 4; a++) {
				Sleep(sleepTime);
				cout << ".";
			}
			cout << b;
		}
		GetCursorPos(&secondPos);
		cout << "*camera click*" << endl;
		cout << "There DONE" << endl;
	}

	if (secondPos.x != 0 && secondPos.y != 0 && firstPos.x != 0 && firstPos.y != 0) {
		settings.open("Settings.txt", fstream::out);

		settings << firstPos.x << " " << firstPos.y
			<< " " << secondPos.x << " " << secondPos.y;

		settings.close();
	}

}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	DWORD dwPID;

	GetWindowThreadProcessId(hwnd, &dwPID);

	if (dwPID == lParam) {
		::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		::vlcone = hwnd;
		return FALSE;
	}

	return TRUE;
}
