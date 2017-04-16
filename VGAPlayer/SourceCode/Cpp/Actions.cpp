#include "InitialSetup.h"
#include "Actions.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;
using namespace GV;

Actions::Actions() {
	doonce = false;
}

//Highlight Overloaded Function
void Actions::highlight(sf::Text &t, string color, float thickness) {
	if (!doonce) {
		c = t.getColor();
		doonce = true;
	}

	if (color.find("dark") != string::npos) {
		t.setOutlineThickness(thickness);
		t.setOutlineColor(sf::Color(150, 150, 150));
	}
	else if (color.find("light") != string::npos) {
		t.setOutlineThickness(thickness);
		t.setOutlineColor(sf::Color(255,255,255));
	}
}

void Actions::highlight(sf::RectangleShape &shape, string color) {
	if (!doonce) {
		c = shape.getFillColor();
		doonce = true;
	}

	if (color.find("dark") != string::npos) {
		shape.setFillColor(sf::Color(c.r - 100, c.g - 100, c.b - 100));
	}
	else if (color.find("light") != string::npos) {
		shape.setFillColor(sf::Color(c.r + 50, c.g + 50, c.b + 50));
	}
}

//deHightlight Overloaded Function
void Actions::deHightlight(sf::Text &t) {
		t.setOutlineThickness(0);
}

void Actions::deHightlight(sf::RectangleShape &shape, sf::Color &c) {
	shape.setFillColor(c);
}


//Hover Overloaded Function
bool Actions::Hover(sf::Text &t) {
	if (t.getGlobalBounds().contains(sf::Vector2f(sfm.mouse.getPosition(sfm.window)))) {
		return true;
	}
	else {
		return false;
	}
}

bool Actions::Hover(sf::RectangleShape &shape) {
	if (shape.getGlobalBounds().contains(sf::Vector2f(sfm.mouse.getPosition(sfm.window)))) {
		return true;
	}
	else {
		return false;
	}
}

bool Actions::Hover(sf::Sprite &s) {
	if (s.getGlobalBounds().contains(sf::Vector2f(sfm.mouse.getPosition(sfm.window)))) {
		return true;
	}
	else {
		return false;
	}
}

//Click function
bool Actions::Click() {
	if (sfm.mouse.isButtonPressed(sf::Mouse::Left)) {
		return true;
	}
	else {
		return false;
	}
}

void Actions::reSync(sf::Time offset) {
	sf::Time newOff;
	if (mod.oneMovie->switchON)
	newOff = sfemov.movie2.getPlayingOffset();

	cout << newOff.asSeconds() << endl;
	cout << sfemov.movie.getPlayingOffset().asMicroseconds() + offset.asSeconds() << endl;

	if (newOff.asSeconds() != sfemov.movie.getPlayingOffset().asSeconds() + offset.asSeconds())
		cout << "offset" << endl;
}

bool Actions::movie2Hover() {
	if (sfm.mouse.getPosition(sfm.window).x > sfemov.movie2.getPosition().x && 
		sfm.mouse.getPosition(sfm.window).x < sfemov.movie2.getPosition().x + (sfemov.movie2.getSize().x / 2) &&
		sfm.mouse.getPosition(sfm.window).y > sfemov.movie2.getPosition().y && 
		sfm.mouse.getPosition(sfm.window).y < sfemov.movie2.getPosition().y + (sfemov.movie2.getSize().y / 2)) {
		return true;
	}
	else {
		return false;
	}
}

int Actions::ffstv() {

	srand(time(NULL));

	int r = rand() % 4;

	if (r != 0) {
		return r;
	}
	else {
		ffstv();
	}

}

int Actions::lerp() {



}