#include "InitialSetup.h"
#include "Actions.h"
#include "GlobalVariables.h"
#include "fanArt.h"
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;
using namespace GV;

fanArt::fanArt(){
}


fanArt::~fanArt(){
}

void fanArt::download() {
	sf::Http fart("fart.videogamesawesome.com");
	sf::Http::Request req;
	req.setMethod(sf::Http::Request::Get);

	string url = "/post/view/" + to_string(Random());
	cout << url << endl;
	req.setUri(url);
	sf::Http::Response fget = fart.sendRequest(req);

	string get = fget.getBody();	
	
	get.erase(0, get.find("/_image"));

	get.erase(get.find("data-width") - 2, get.length());
	cout << get << endl;
	req.setUri(get);
	req.setMethod(sf::Http::Request::Get);

	fget = fart.sendRequest(req);

	Sleep(100);
	doonce = false;
	if (get.find("_image") != string::npos) {
		te.loadFromMemory(fget.getBody().c_str(), fget.getBody().size());
		te.setSmooth(true);

		oriWidth = te.getSize().x;
		oriHeight = te.getSize().y;

		stest.setTexture(te);
		scale();
		stest.setPosition(0, 0);
	}
	
}

int fanArt::Random() {

	srand(time(NULL));

	int r = rand() % 500;

	if (r < 5 || r == 500 || r == 56) {
		Random();
	}
	else {
		return r;
	}

}

void fanArt::scale() {

	wantedWidth = window.getSize().x / 2;
	wantedHeight = window.getSize().y / 2;

	cout << wantedHeight << "  " << wantedWidth << endl;
	cout << oriHeight << "   " << oriWidth << endl;
	////if (oriWidth > wantedWidth) {
	//	buffx = wantedHeight * (oriWidth / oriHeight);
	//	newWidth = buffx / oriWidth;
	//	newHeight = newWidth;
	////}
	//else if (oriHeight > wantedHeight) {
		buffy = (oriWidth / oriHeight) * wantedWidth;
			cout << buffy << endl;
		newHeight = buffy / oriHeight;
			cout << newHeight << endl;
		newWidth = newHeight;
			cout << newWidth << endl;
		doonce = true;
	//}

	cout << newWidth << "  " << newHeight << endl;

	stest.scale(newWidth, newHeight);
}