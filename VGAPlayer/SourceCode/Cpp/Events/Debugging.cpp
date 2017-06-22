#include "GlobalVariables.h"

using namespace std;
using namespace GV;

Debugging::Debugging() {
	bg.setPosition(sf::Vector2f((float)sfm.mouse.getPosition(sfm.window).x, (float)sfm.mouse.getPosition().y));
	bg.setFillColor(sf::Color(140, 140, 140));
	bg.setOutlineColor(sf::Color(170, 170, 170));
	bg.setOutlineThickness(5.f);
	bg.setSize(sf::Vector2f(150, 70));

	write.setFont(sfm.sysFont);
	write.setString("0.00");
	write.setPosition(sf::Vector2f(bg.getPosition().x, bg.getPosition().y));
	write.setCharacterSize(50);
}

void Debugging::valueField() {
	if (sfm.event.type == sf::Event::TextEntered) {
		if (sfm.event.text.unicode == 8 && value.size() > 0) {
			value.pop_back();
		}
		else if (sfm.event.text.unicode == 13) {
			writing = false;
			convValue = stof(value);
		}
		else {
			if (str.limitList.find((char)sfm.event.text.unicode) != string::npos) {
				value.push_back((char)sfm.event.text.unicode);
			}
		}
		write.setString(value);
	}
}

void Debugging::draw() {
	sfm.window.draw(bg);
	sfm.window.draw(write);
}