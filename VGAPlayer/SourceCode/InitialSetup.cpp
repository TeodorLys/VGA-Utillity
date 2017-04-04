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

using namespace std;
using namespace GV;

InitialSetup::InitialSetup()
{
}


InitialSetup::~InitialSetup()
{
}

void InitialSetup::movieWindow() {
	if (!movie.openFromFile(...)) {
		cout << "could not open movie" << endl;
	}
	if (!movie2.openFromFile(...)) {
		cout << "could not open movie" << endl;
	}

	turbo t;
	sf::Image icon;
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	float w = min(static_cast<float>(desktopMode.width), movie.getSize().x);
	float h = min(static_cast<float>(desktopMode.height), movie.getSize().y);

	if (w * h < 1.f) {
		w = max(w, 250.f);
		h = max(h, 40.f);
	}

	window.create(sf::VideoMode(w, h), "VGAPlayer", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	icon.create(32, 32, t.turboBuddy);

	window.setIcon(32, 32, icon.getPixelsPtr());

	movie2.setScale(window.getSize().x / (window.getSize().x * 2.f), window.getSize().y / (window.getSize().y * 2.f));
	movie2.fit(0, 0, w, h);
	movie2.play();
	movie2.setPosition(w / 2, 0);

	cout << w << " " << h << endl;
	cout << movie2.getPosition().x << " " << movie2.getPosition().y << endl;

	movie.fit(0, 0, w, h);
	movie.play();
	movie.setVolume(0);
	movie2.setVolume(0);
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

void InitialSetup::UI() {
}
