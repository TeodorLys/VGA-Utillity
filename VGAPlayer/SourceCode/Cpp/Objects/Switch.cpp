#include "Switch.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace GV;

Switch::Switch() {
}

void Switch::setBase() {

	base.setSize(sf::Vector2f(10, 6));
	if(!switchON)
		base.setFillColor(sf::Color(220, 100, 100));
	else 
		base.setFillColor(sf::Color(100, 220, 100));
	base.setOutlineThickness(1);
	base.setOutlineColor(sf::Color(255, 125, 0));
	base.setOrigin(base.getSize().x / 2, base.getSize().y / 2);
	setSwitch();

	base.setScale(5, 5);
	swit.setScale(5, 5);

}

void Switch::setScale(sf::Vector2f scale) {
	base.setScale(scale);
	swit.setScale(scale);
}

void Switch::setSwitch() {
	
	swit.setOutlineThickness(1.f);
	swit.setOutlineColor(sf::Color(220, 220, 220));
	swit.setSize(sf::Vector2f(base.getSize().x / 2 - (swit.getOutlineThickness()),
		                      base.getSize().y - (swit.getOutlineThickness() * 2)));

	swit.setOrigin(swit.getSize().x / 2, swit.getSize().y / 2);
	swit.setFillColor(sf::Color(200, 200, 200));
	
}

void Switch::setPosition(sf::Vector2f pos) {
	base.setPosition(pos);

	if (!switchON) 
		swit.setPosition(pos.x - base.getSize().x, pos.y);
	else
		swit.setPosition(pos.x + base.getSize().x, pos.y);
}

bool Switch::clickSwitch() {
	if (base.getGlobalBounds().contains(sf::Vector2f(sfm.mouse.getPosition(sfm.window))) &&
		obj.actions.Click()) {

		if (!switchON) {
			base.setFillColor(sf::Color(100, 220, 100));
			swit.setPosition(base.getPosition().x + base.getSize().x, 
				             base.getPosition().y);
			switchON = true;
			return true;
		}
		else if (switchON) {
			base.setFillColor(sf::Color(220, 100, 100));
			swit.setPosition(base.getPosition().x - base.getSize().x, 
				             base.getPosition().y);
			switchON = false;
			return true;
		}
	}
	else {
		return false;
	}
}

void Switch::draw() {
	sfm.window.draw(base);
	sfm.window.draw(swit);
}
