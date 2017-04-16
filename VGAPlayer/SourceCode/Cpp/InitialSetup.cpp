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
}//Constructor

void InitialSetup::movieWindow() {

	turbo t;
	sf::Image icon;

	ImportfromFile();

	sfm.window.create(sf::VideoMode(value.width, value.height), "VGAPlayer", sf::Style::Close | sf::Style::Resize);
	sfm.window.setFramerateLimit(60);
	sfm.window.setVerticalSyncEnabled(true);

	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	value.w = static_cast<float>(desktopMode.width);
	value.h = static_cast<float>(desktopMode.height);

	icon.create(32, 32, t.turboBuddy);

	sfm.window.setIcon(32, 32, icon.getPixelsPtr());

	//The menu background
	sfm.theCrew.setSize(sf::Vector2f(image.getSize().x, image.getSize().y));
	sfm.theCrew.setOrigin(sfm.theCrew.getSize().x / 2, sfm.theCrew.getSize().y / 2);
	sfm.theCrew.setPosition(sfm.window.getSize().x / 2, 300);

	//"Fullscreen" movie Volume
	setText(sfm.vol1, to_string(value.mov2Vol), sf::Vector2f(0, 0));

	//Smaller movie Volume
	setText(sfm.vol2, to_string(value.mov2Vol), sf::Vector2f(sfm.window.getSize().x, 0));
	
	//"Fullscreen" movie timer
	setText(sfm.tTimer, "0", sf::Vector2f(0, sfm.window.getSize().y - sfm.tTimer.getGlobalBounds().height));

	//Smaller movie timer
	setText(sfm.smalltTimer, "0", sf::Vector2f(sfm.window.getSize().x, sfm.window.getSize().y));

	//Load Base Background
	if(!sfm.base.loadFromFile("base.png")){
		value.msg = MessageBox(NULL, L"COULD NOT LOAD IMAGE", L"INVALID FILE PATH", MB_RETRYCANCEL);
	}
	
	sfm.b.setTexture(&sfm.base);
	sfm.b.setSize(sf::Vector2f(sfm.window.getSize().x, sfm.window.getSize().y));

}//MovieWindow Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Imports all images and textures
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::ImportfromFile() {
	string background;

	if (obj.actions.ffstv() == 1) {
		background = "FFSTV.png";
	}
	else if (obj.actions.ffstv() == 2) {
		background = "FFSTVmario.png";
	}
	else if (obj.actions.ffstv() == 3) {
		background = "FFSTVps.png";
	}
	else {
		background = "FFSTV.png";
	}

	//For some reason I have to load an Image... and then to a Texture
	if (!image.loadFromFile(background)) {
		value.msg = MessageBox(NULL, L"COULD NOT LOAD IMAGE\nSOMETHING HAS BEEN DELETED", L"IMAGE NOT LOADED", MB_OKCANCEL);
		if (value.msg == IDOK || value.msg == IDCANCEL)
			exit(-1);
	}
	else {
		if (!sfm.ffsBG.loadFromImage(image)) {
			value.msg = MessageBox(NULL, L"COULD NOT LOAD IMAGE\nSOMETHING HAS BEEN DELETED", L"IMAGE NOT LOADED", MB_OKCANCEL);
			if (value.msg == IDOK || value.msg == IDCANCEL)
				exit(-1);
			exit(-1);
		}
		else {
			sfm.theCrew.setTexture(&sfm.ffsBG);
		}
	}

	if (!sfm.font.loadFromFile("VGAFont.ttf")) {
		if (!sfm.font.loadFromFile("c:\\windows\\fonts\\arial.ttf")) {
			value.msg = MessageBox(NULL, L"DEFAULT FONT COULD NOT BE LOADED", L"FONT NOT LOADED", MB_RETRYCANCEL);
			if (value.msg == IDCANCEL) {
				exit(-1);
			}
			else if (value.msg == IDRETRY) {
				if (!sfm.font.loadFromFile("c:\\windows\\fonts\\arial.ttf")) {
					value.msg = MessageBox(NULL, L"DEFAULT FONT COULD NOT BE LOADED", L"FONT NOT LOADED", MB_OKCANCEL);
					if (value.msg == IDCANCEL && value.msg == IDOK)
						exit(-1);
				}//Default font retry load END
			}//Default Font load fail click retry END
		}//Default font load END
	}//VGAFont load END
}//Import from file Function END


///////////////////////////////////////////////////////////////////////////////////////////
/// \Creates or gets information from Settings file
///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::files(){
	fstream paths;
	string buff;
	
	str.current = boost::filesystem::current_path();

	if (boost::filesystem::exists("Settings.txt")) {
		paths.open("Settings.txt", fstream::in);
		if (paths.is_open()) {
			getline(paths, buff);
			if (buff.find_first_of("volume1: ") != string::npos) {
				buff.erase(0, buff.find_last_of("volume1: ") + 1);
				value.mov1Vol = atoi(buff.c_str());
			}

			getline(paths, buff);

			if (buff.find_first_of("volume2: ") != string::npos) {
				buff.erase(0, buff.find_last_of("volume2: ") + 1);
				value.mov2Vol = atoi(buff.c_str());
			}
		}
		paths.close();
	}
	else {
		paths.open("Settings.txt", fstream::out);
		paths << "volume1: 0" << endl;
		paths << "volume2: 0" << endl;
		paths.close();
	}
}//Files Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Creates an open file prompt
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::openFile(int n) {
	OPENFILENAMEA file;
	string s;
	char c[256];
	HANDLE h;
	HWND hwnd = NULL;
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.hwndOwner = sfm.window.getSystemHandle();
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
}//Open file Function END



void InitialSetup::UI() {
}

///////////////////////////////////////////////////////////////////////////////////////////
/// \Loads the movies into memory
///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::LoadMovie(int n) {
	openFile(n);

	if (ffs != "NONE" || mov != "NONE") {
		wstring t;

		if (n == 1) {
			if (!sfemov.movie.openFromFile(ffs)) {
				string h = "Could not open\n" + ffs;
				t = wstring(h.begin(), h.end());
				LPCWSTR message = t.c_str();
				value.msg = MessageBox(NULL, message, L"PATH WAS NOT FOUND", MB_RETRYCANCEL);
			}
		}
		else {
			if (!sfemov.movie2.openFromFile(mov)) {
				string h = "Could not open\n" + mov;
				t = wstring(h.begin(), h.end());
				LPCWSTR message = t.c_str();
				value.msg = MessageBox(NULL, message, L"PATH WAS NOT FOUND", MB_RETRYCANCEL);
			}
		}
	}
}//LoadMovie Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Sets all settings for text objects
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::setText(sf::Text &t, string str, sf::Vector2f pos) {
	t.setString(str);
	t.setCharacterSize(32);
	t.setScale(1, 1);
	t.setFillColor(sf::Color(255, 255, 255));
	t.setFont(sfm.font);
	t.setStyle(sf::Text::Regular);
	t.setPosition(pos);
}//SetText Function END
