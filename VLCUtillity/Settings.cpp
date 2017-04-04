#include "playPause.h"
#include "Settings.h"
#include "GlobalVariables.h"
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <boost\filesystem.hpp>
#include <iostream>

using namespace std;
using namespace GV;

Settings::Settings()
{
}


Settings::~Settings(){
	if (boost::filesystem::exists("Settings.txt")) {
		settings.open("Settings.txt", fstream::out);
		settings << firstPos.x << " " << firstPos.y
			<< " " << secondPos.x << " " << secondPos.y << endl;;
	}
	else {
		settings.open("Settings.txt", fstream::out);
		settings << 0 << " " << 0 << " " << 0 << " " << 0 << endl;

	}

	settings << "hideWindow: ";

	if (hideWindow)
		settings << "true" << endl;
	else
		settings << "false" << endl;

	settings.close();
}

///Initial Settings
void Settings::SetupStuff() {
	string buff;
	settings.open("Settings.txt", fstream::in);
///If settings could be opened
	if (settings.is_open()) {
		//Gets the saved cursor position
		while (settings >> firstPos.x >> firstPos.y >> secondPos.x >> secondPos.y);
		settings.close();
		//But then to get the next inline I need to close the file and
		//open it again... Probably exists a better way
		settings.open("Settings.txt", fstream::in);
		//Cycles though the newly opened file
		for (string buff; getline(settings, buff);) {
			//Gets the hide window settings
			if (buff.find("hideWindow") != string::npos) 
				hideWindow = findBool(buff);
		}
	}

	///If the path settings exists
	if (boost::filesystem::exists("Path.txt")) {
		path.open("Path.txt", fstream::in);
		getline(path, buff);
		getline(path, font);
		path.close();
		if (font != "") {

			if (font.find(".ttf") == string::npos) {
				font += ".ttf";
			}
		    tryagain:
			if (!boost::filesystem::exists(font)) {
				path.close();
				msg = MessageBoxW(NULL, L"Font path was not found\nplease check the path and try again",
					              L"BAD FONT PATH", MB_RETRYCANCEL);
				    if (msg == 4)
					goto tryagain;
			}//If font path Exists
		}//If font is not NULL END
		else {
			path.open("Path.txt", fstream::out);
			path << buff << endl << "C:/windows/fonts/arial.ttf";
			path.close();
		}//Else font not NULL END
	}//If path exists END
	///If the path settings file does not exits
	else {
		path.open("Path.txt", fstream::out);
		path << "c:/program files (x86)/videolan/vlc/vlc.exe" << endl << "c:/windows/fonts/arial.ttf";
		font = "c:/windows/fonts/arial.ttf";
		path.close();
	}//If path does not exists END

	///Just debug... if I forgot to close the files somewhere 
	if (settings.is_open()) {
		settings.close();
	}

	if (path.is_open()) {
		path.close();
	}

}//SetupsStuff END

///Gets the setting and finds if it is true or false
bool Settings::findBool(string &b) {
	if (b.find("true") != string::npos) {
		return true;
	}
	else if (b.find("false") != string::npos) {
		return false;
	}
	//Default to false
	else {
		return false;
	}
}
