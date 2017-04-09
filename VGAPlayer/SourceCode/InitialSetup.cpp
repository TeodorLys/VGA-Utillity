#include "InitialSetup.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Turbo.h"
#include <boost\filesystem.hpp>
#include <string>
#include <algorithm>

using namespace std;
using namespace GV;

InitialSetup::InitialSetup(){
	ffs = "NONE";
	mov = "NONE";
}


InitialSetup::~InitialSetup()
{
}

void InitialSetup::movieWindow() {

	turbo t;
	sf::Image icon;
	sf::Image image;
	

	if (!image.loadFromFile("screenshot.png")) {
		exit(-1);
	}
	else {
		if (!ffsBG.loadFromImage(image)) {
			exit(-1);
		}
		else {
			ffssp[0].setTexture(&ffsBG);
		}
	}

	window.create(sf::VideoMode(width, height), "VGAPlayer", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	ffssp[0].setPosition(0, 0);
	ffssp[0].setScale(1, 1);
	ffssp[0].setSize(sf::Vector2f(window.getSize().x, window.getSize().x * 9 / 16));

	ffssp[1].setPosition(window.getSize().x / 2, ffssp[0].getSize().y - 100);
	ffssp[1].setScale(1, 1);
	ffssp[1].setSize(sf::Vector2f(100, 50));
	ffssp[1].setFillColor(sf::Color(200,200,200));
	ffssp[1].setOutlineColor(sf::Color(150,150,150));
	ffssp[1].setOutlineThickness(5.f);


	icon.create(32, 32, t.turboBuddy);

	window.setIcon(32, 32, icon.getPixelsPtr());


	font.loadFromFile("VGAFont.ttf");
	vol1.setString("0");
	vol1.setCharacterSize(32);
	vol1.setScale(1, 1);
	vol1.setFillColor(sf::Color(255, 255, 255));
	vol1.setFont(font);
	vol1.setStyle(sf::Text::Bold);
	vol1.setPosition(0, 0);

	vol2.setString("0");
	vol2.setCharacterSize(32);
	vol2.setScale(1, 1);
	vol2.setFillColor(sf::Color(255, 255, 255));
	vol2.setFont(font);
	vol2.setStyle(sf::Text::Bold);
	//vol2.setOrigin(vol2.getScale().x, 0);
	vol2.setPosition(window.getSize().x - 60, 0);

	OMov.setFont(font);
	OMov.setCharacterSize(32);
	OMov.setString("Open Movie file");
	OMov.setStyle(sf::Text::Bold);
	OMov.setFillColor(sf::Color(255,100,0));
	OMov.setPosition(window.getSize().x / 2 + 200, 100);
	
	OVGA.setFont(font);
	OVGA.setCharacterSize(32);
	OVGA.setString("Open FFStv file");
	OVGA.setStyle(sf::Text::Bold);
	OVGA.setFillColor(sf::Color(255, 100, 0));
	OVGA.setPosition(100, 200);

	tPlay.setString("Play");
	tPlay.setFont(font);
	tPlay.setCharacterSize(32);
	tPlay.setFillColor(sf::Color(0, 0, 0));
	tPlay.setPosition(ffssp[1].getPosition().x + 15, ffssp[1].getPosition().y + 2);



}

void InitialSetup::files(){
	fstream paths;
	string buff;
	if (boost::filesystem::exists("Settings.txt")) {
		paths.open("Settings.txt", fstream::in);
		if (paths.is_open()) {
			getline(paths, buff);
			if (buff.find_first_of("ATP: ") != string::npos) {
				buff.erase(0, buff.find("ATP: "));
				APTpath = buff;
			}

			getline(paths, buff);

			if (buff.find_first_of("Movie: ") != string::npos) {
				buff.erase(0, buff.find("Movie: "));
				moviePath = buff;
			}
		}
		paths.close();

		cout << moviePath << endl;
		cout << APTpath << endl;

	}
	else {
		paths.open("Settings.txt", fstream::out);
		paths << "APT: " << endl;
		paths << "Movie: " << endl;
		paths.close();
	}
}

void InitialSetup::openFile(int n) {
	OPENFILENAMEA file;
	string s;
	char c[256];
	HANDLE h;
	HWND hwnd = NULL;
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.hwndOwner = window.getSystemHandle();
	file.lpstrFile = c;
	file.lpstrFile[0] = '\0';
	file.nMaxFile = sizeof(c);
	file.nFilterIndex = 1;
	file.lpstrFileTitle = NULL;
	file.nMaxFileTitle = 0;
	file.lpstrInitialDir = NULL;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&file) == TRUE) {
		h = CreateFileA(file.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

		CloseHandle(h);

		if (c != "") {
			s = c;
		}

		if (n == 1) {
			ffs = s;
		}
		else {
			mov = s;
		}
	}

}

void InitialSetup::UI() {
}

void InitialSetup::LoadMovie(int n) {
	openFile(n);
	wstring t;

	cout << ffs << "   " << mov << endl;

	if (n == 1) {
		if (!movie.openFromFile(ffs)) {
			string h = "Could not open\n" + ffs;
			t = wstring(h.begin(), h.end());
			LPCWSTR message = t.c_str();
			int msg = MessageBox(NULL, message, L"PATH WAS NOT FOUND", MB_RETRYCANCEL);
		}
	}
	else {
		if (!GV::movie2.openFromFile(mov)) {
			string h = "Could not open\n" + mov;
			t = wstring(h.begin(), h.end());
			LPCWSTR message = t.c_str();
			int msg = MessageBox(NULL, message, L"PATH WAS NOT FOUND", MB_RETRYCANCEL);
		}
	}
}
