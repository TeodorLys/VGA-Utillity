#include "InitialSetup.h"
#include "Actions.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>

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
	if (t.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
		return true;
	}
	else {
		return false;
	}
}

bool Actions::Hover(sf::RectangleShape &shape) {
	if (shape.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
		return true;
	}
	else {
		return false;
	}
}

bool Actions::Hover(sf::Sprite &s) {
	if (s.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
		return true;
	}
	else {
		return false;
	}
}

//Click function
bool Actions::Click() {
	if (mouse.isButtonPressed(sf::Mouse::Left)) {
		return true;
	}
	else {
		return false;
	}
}