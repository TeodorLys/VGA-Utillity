#include "InitialSetup.h"
#include "GlobalVariables.h"
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Turbo.h"
#include "SaveSettings.h"
#include <boost\filesystem.hpp>
#include <boost\lambda\bind.hpp>
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

	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	value.w = static_cast<float>(desktopMode.width);   //Get main monitor width
	value.h = static_cast<float>(desktopMode.height);   //Get main monitor height

	sfm.window.create(sf::VideoMode((int)value.w, (int)value.h), "VGAPlayer", sf::Style::Close | sf::Style::Resize);   //Creates the actual window
	sfm.window.setFramerateLimit(60);   //Framerate limit
	sfm.window.setVerticalSyncEnabled(true);   //Since this is something moving, why not add some vSync
	
	ShowWindow(sfm.window.getSystemHandle(), SW_MAXIMIZE);
	
	icon.create(32, 32, t.turboBuddy);   //Program icon

	sfm.window.setIcon(32, 32, icon.getPixelsPtr());

	//The menu background
	sfm.theCrew.setSize(sf::Vector2f((float)image.getSize().x, (float)image.getSize().y));
	sfm.theCrew.setOrigin((float)sfm.theCrew.getSize().x / 2, (float)sfm.theCrew.getSize().y / 2);
	sfm.theCrew.setPosition((float)sfm.window.getSize().x / 2, 300);

	//"Fullscreen" movie Volume
	setText(sfm.vol1, to_string((int)value.mov2Vol), sf::Vector2f(0, 0), 32, sfm.font);

	//Smaller movie Volume
	setText(sfm.vol2, to_string((int)value.mov2Vol), sf::Vector2f((float)sfm.window.getSize().x, 0), 32, sfm.font);
	
	//"Fullscreen" movie timer
	setText(sfm.tTimer, "0", sf::Vector2f(0, sfm.window.getSize().y - sfm.tTimer.getGlobalBounds().height), 32, sfm.font);

	//Smaller movie timer
	setText(sfm.smalltTimer, "0", sf::Vector2f((float)sfm.window.getSize().x, (float)sfm.window.getSize().y), 32, sfm.font);

	//Load Base Background
	if(!sfm.base.loadFromFile("base.png")){
		value.msg = MessageBox(NULL, L"COULD NOT LOAD IMAGE", L"INVALID FILE PATH", MB_RETRYCANCEL);
	}
	
	sfm.b.setTexture(&sfm.base);
	sfm.b.setSize(sf::Vector2f((float)sfm.window.getSize().x, (float)sfm.window.getSize().y));

	obj.me.contextMenuSetup();
}//MovieWindow Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Imports all images and textures
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::ImportfromFile() {
	string background;

	string t = boost::filesystem::temp_directory_path().string();   //Gets the drive letter of where windows is installed

	t.erase(1, t.length());

	string safeFontPath = t + ":\\windows\\fonts\\arial.ttf";   //If vgafont is not found

	string sysFontPath = t + ":\\windows\\fonts\\segoeui.ttf";   //For all system stuff, context menu etc...

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

	//Tries to load the SEGOEUI font
	if (!sfm.sysFont.loadFromFile(sysFontPath)) {
		//if failed...
		value.msg = MessageBox(NULL, L"COULD NOT LOAD SYSTEM FONT", L"PATH NOT FOUND", MB_OKCANCEL);
		//What the user clicks on the messagebox
		if (value.msg == IDCANCEL || value.msg == IDOK) {
			exit(-1);
		}
	}

	//Tries to load the VGAfont
	if (!sfm.font.loadFromFile("VGAFont.ttf")) {
		//If failed, Try to load Arial font
		if (!sfm.font.loadFromFile(safeFontPath)) {
			//If failed...
			value.msg = MessageBox(NULL, L"DEFAULT FONT COULD NOT BE LOADED", L"FONT NOT LOADED", MB_RETRYCANCEL);
			if (value.msg == IDCANCEL) {
				exit(-1);
			}
			else if (value.msg == IDRETRY) {
				if (!sfm.font.loadFromFile(safeFontPath)) {
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
	string buff;
	string file;

	str.current = boost::filesystem::current_path();

	//So I am not trying to open a file that doesnt exist
	if (boost::filesystem::exists("config/Settings.ini")) {
		str.setting.open("config/Settings.ini", fstream::in);
		if (str.setting.is_open()) {

			save.settings.vecPush(save.volume1);
			save.settings.vecPush(save.volume2);
			save.settings.loadSettings(str.setting);
			
			int buff = 0;
			save.volume1.getV(buff);
			value.mov1Vol = buff;

			buff = 0;
			save.volume2.getV(buff);
			value.mov2Vol = buff;
		}
		str.setting.close();
	}
	//Creates the settings file, if it doesnt exist
	else {
		str.setting.open("config/Settings.ini", fstream::out);
		save.settings.saveVariable(save.volume1, str.setting);
		save.settings.saveVariable(save.volume2, str.setting);
		str.setting.close();
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

		if (c != "")
			s = c;

		if (n == 1)
			ffs = s;
		else
			mov = s;
	}
}//Open file Function END


/*----(NOT IN USE)---*/
void InitialSetup::UI() {
}


///////////////////////////////////////////////////////////////////////////////////////////
/// \Loads the movies into memory
///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::LoadMovie(int n) {
	openFile(n);

	//So it doesnt try to load a file that has not been selected, i.e "NONE" is defalt (which is not a path...)
	if (ffs != "NONE" || mov != "NONE") {
		wstring t;
		string h;
		LPCWSTR message;
		//Load the first movie
		if (n == 1) {
			delete sfemov.movie;
			sfemov.movie = new sfe::Movie;
			if (!sfemov.movie->openFromFile(ffs)) {
				h = "Could not open\n" + ffs;
				t = wstring(h.begin(), h.end());
				message = t.c_str();
				value.msg = MessageBox(NULL, message, L"PATH WAS NOT FOUND", MB_RETRYCANCEL);
			}
			else {
				mod.ffstv->outLine = sf::Color(20, 255, 20);
				mod.ffstv->setButtonColor(5.5f);
			}
		}
		//Load the second movie
		else {
			delete sfemov.movie2;
			sfemov.movie2 = new sfe::Movie;
			if (!sfemov.movie2->openFromFile(mov)) {
				h = "Could not open\n" + mov;
				t = wstring(h.begin(), h.end());
				message = t.c_str();
				value.msg = MessageBox(NULL, message, L"PATH WAS NOT FOUND", MB_RETRYCANCEL);
			}
			else {
				mod.film->outLine = sf::Color(20, 255, 20);
				mod.film->setButtonColor(5.5f);
			}

			if (sfemov.movie2->getSize().x / sfemov.movie2->getSize().y > 2) {
				obj.actions.SetLimits(960 / (1920.f / sfm.window.getSize().x), 455 / (1080.f / sfm.window.getSize().y));
				bools.movie2Greater = true;
			}
			else if (sfemov.movie2->getSize().x / sfemov.movie2->getSize().y < 2) {
				obj.actions.SetLimits(930 / (1920.f / sfm.window.getSize().x), 510 / (1080.f / sfm.window.getSize().y));
				bools.movie2Greater = false;
			}
		}
	}

	if (ffs != "NONE" && mov != "NONE") {
		hashMovies();
		CheckMovieWatched();
	}
}//LoadMovie Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Sets all settings for text objects
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::setText(sf::Text &t, string str, sf::Vector2f pos, unsigned int charSize, sf::Font &font) {
	t.setString(str);
	t.setCharacterSize(charSize);
	t.setScale(1, 1);
	t.setFillColor(sf::Color(255, 255, 255));
	t.setFont(font);
	t.setStyle(sf::Text::Regular);
	t.setPosition(pos);
}//SetText Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Initializes all of the menu buttons an switches									 ///
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::menuButtonsSettings() {

	//Sets the PLAY Button settings
	setButtons(*mod.play, 20, 20, "PLAY", sf::Color(50, 50, 50),
		sf::Color(100, 65, 0), 5.5f, sf::Color(100, 65, 0),
		sf::Vector2f(sfm.window.getSize().x / 2.f, sfm.window.getSize().y - 100.f), (sfm.window.getSize().x / value.width) * 2,
		(sfm.window.getSize().y / value.height) * 2, 7);

	//Sets the OPEN FFSTV VIDEO settings
	setButtons(*mod.ffstv, 20, 20, "OPEN FFSTV VIDEO", sf::Color(0, 0, 0),
		sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f(200.f, sfm.window.getSize().y - 100.f), sfm.window.getSize().x / value.width, sfm.window.getSize().y / value.height, 5);

	//Sets the OPEN MOVIE FILE settings
	setButtons(*mod.film, 20, 20, "OPEN MOVIE FILE", sf::Color(0, 0, 0),
		sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f(sfm.window.getSize().x - 200.f, sfm.window.getSize().y - 100.f), sfm.window.getSize().x / value.width, sfm.window.getSize().y / value.height, 5);

	setButtons(*mod.replay, 20, 20, "Replay", sf::Color(50, 50, 50, 0),
		sf::Color(255, 125, 0, 0), 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f((float)sfm.window.getSize().x / 2 + (sfm.window.getSize().x / 8), (float)sfm.window.getSize().y / 2), sfm.window.getSize().x / value.width, sfm.window.getSize().y / value.height, 5);

	setButtons(*mod.ret, 20, 20, "Return", sf::Color(50, 50, 50, 0),
		sf::Color(255, 125, 0, 0), 5.5f, sf::Color(255, 125, 0),
		sf::Vector2f((float)sfm.window.getSize().x / 2 - (sfm.window.getSize().x / 8), (float)sfm.window.getSize().y / 2), sfm.window.getSize().x / value.width, sfm.window.getSize().y / value.height, 5);

	setSwitches(*mod.oneMovie, 5, sf::Vector2f(mod.play->getPosition().x, mod.play->getPosition().y - (mod.play->getSize().y)));
}

//Sets the initial Buttons variables
void InitialSetup::setButtons(Buttons &b, float sX, float sY, string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY, float extra) {
	b.setSize(sX, sY);
	b.setText(text);
	b.setScale(sf::Vector2f(scaleX, scaleY));
	b.baseColor = sf::Color(c);
	b.outLine = sf::Color(out);
	b.setButtonColor(outsize);
	b.setTextColor(tc);
	b.setPosition(p, extra);
	b.baseColor = sf::Color(c);
	b.outLine = sf::Color(out);
}

void InitialSetup::setSwitches(Switch &s, float size, sf::Vector2f pos) {
	s.setBase();
	s.setScale(sf::Vector2f(size, size));
	s.setPosition(sf::Vector2f(pos));
}

void InitialSetup::Movie2Limits() {
	if (bools.movie2Greater) {
		obj.actions.SetLimits(960 / (1920.f / sfm.window.getSize().x), 455/ (1080.f / sfm.window.getSize().y));
	}
	else if (!bools.movie2Greater) {
		obj.actions.SetLimits(930 / (1920.f / sfm.window.getSize().x), 510 / (1080.f / sfm.window.getSize().y));
	}
}

void InitialSetup::CheckMovieWatched() {
	string buff;
	string file = str.current.string() + "\\config\\movieSave0.ini";
	float fbuff;
	int index = 0;
	for (int a = 0; a < allHash.size(); a++) {
		if(allHash[a] == combHash){
			index = a;
			goto Success;
			break;
		}
	}
	cout << "index: " << index << endl;
	file = str.current.string() + "\\config\\movieSave" + to_string(allHash.size()) + ".ini";
	str.movieSavePath = file;
	allHash.push_back(combHash);

	return;
Success:
	file = str.current.string() + "\\config\\movieSave" + to_string(index) + ".ini";
	str.movieSavePath = file;
	moviePreset(buff, fbuff, file);
	loadPreset(buff, fbuff);
}

void InitialSetup::moviePreset(string buff, float fbuff, string file) {
	
	if (boost::filesystem::exists(file)) {
		str.movieFile.open(file, fstream::in);
		
		if (str.movieFile.is_open()) {
			save.saveMovies.vecPush(save.mov1Time);
			save.saveMovies.vecPush(save.mov2Time);
			save.saveMovies.vecPush(save.mov2Offset);
			save.saveMovies.vecPush(save.mov1Path);
			save.saveMovies.vecPush(save.mov2Path);
			
			save.saveMovies.loadSettings(str.movieFile);
		}
		str.movieFile.close();
	}
	else {
		str.movieFile.open(file, fstream::out);
		save.saveMovies.saveVariable(save.mov1Time, str.movieFile);
		save.saveMovies.saveVariable(save.mov2Time, str.movieFile);
		save.saveMovies.saveVariable(save.mov2Offset, str.movieFile);
		save.saveMovies.saveVariable(save.mov1Path, str.movieFile);
		save.saveMovies.saveVariable(save.mov2Path, str.movieFile);
		str.movieFile.close();
	}
	str.movieFile.close();
}

void InitialSetup::loadPreset(string buff, float fbuff) {
	save.mov1Time.getV(fbuff);
	value.mov1SaveTime = fbuff;

	save.mov2Time.getV(fbuff);
	value.mov2SaveTime = fbuff;

	save.mov2Offset.getV(fbuff);
	value.mov2OffsetTime = fbuff;

	save.mov1Path.getV(buff);
	str.APTpath = buff;

	save.mov2Path.getV(buff);
	str.moviePath = buff;
}

void InitialSetup::rollBackPreset() {
	save.saveMovies.SA.pop_back();
	save.saveMovies.SA.pop_back();
	save.saveMovies.SA.pop_back();
	save.saveMovies.SA.pop_back();
	save.saveMovies.SA.pop_back();
}

void InitialSetup::unloadPreset() {
	save.mov1Time.setV(0.f);
	value.mov1SaveTime = 0;

	save.mov2Time.setV(0.f);
	value.mov2SaveTime = 0;

	save.mov2Offset.setV(0.f);
	value.mov2OffsetTime = 0;

	str.APTpath = "";

	str.moviePath = "";
}

void InitialSetup::hashMovies() {
	fstream fhash;

	string buff = str.current.string() + "\\config\\hash.vga";

	if (!boost::filesystem::exists(buff)) {
		fhash.open(buff, fstream::out);
		fhash.close();
	}
	else {
		fhash.open(buff, fstream::in);
		for (string s; getline(fhash, s);) {
			cout << s << endl;
			allHash.push_back(atoi(s.c_str()));
		}
		fhash.close();
	}
	size_t ffsHash = hash<string>{}(ffs);
	size_t movHash = hash<string>{}(mov);

	combHash = ffsHash + movHash;
}