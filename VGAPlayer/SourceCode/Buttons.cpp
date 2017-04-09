#include "Buttons.h"
#include "GlobalVariables.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace GV;

Buttons::Buttons(){
	HeightAdd = 50;
}


Buttons::~Buttons(){
}

void Buttons::setText(string str) {
	title.setString(str);
	title.setFont(font);
	title.setCharacterSize(32);
	title.setStyle(sf::Text::Regular);
	title.setScale(1, 1);
	rectangle();
	title.setOrigin(sf::Vector2f(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2));
}

void Buttons::setScale(sf::Vector2f vec) {
	title.setScale(vec);
	b.setSize(sf::Vector2f(title.getGlobalBounds().width + WidthAdd, title.getGlobalBounds().height + HeightAdd));
	b.setOrigin(sf::Vector2f(b.getSize().x / 2, b.getSize().y / 2));
}

void Buttons::setTextColor(sf::Color c) {
	title.setFillColor(c);
}

void Buttons::setButtonColor(sf::Color c, sf::Color outline, float line) {
	b.setFillColor(c);
	b.setOutlineColor(outline);
	b.setOutlineThickness(line);
}

void Buttons::draw() {
	window.draw(b);
	window.draw(title);
}

void Buttons::rectangle() {
	b.setSize(sf::Vector2f(title.getGlobalBounds().width + WidthAdd, title.getGlobalBounds().height + HeightAdd));
	b.setOrigin(sf::Vector2f(b.getSize().x / 2, b.getSize().y / 2));
}

void Buttons::setSize(float h, float w) {
	HeightAdd = h;
	WidthAdd = w;
}

void Buttons::setPosition(sf::Vector2f pos) {
	b.setPosition(pos);
	title.setPosition(b.getPosition().x, b.getPosition().y - 5);
	
}

bool Buttons::Hover(sf::Color c, float size) {
	if (b.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window)))) {
		title.setOutlineColor(c);
		title.setOutlineThickness(size);
		return true;
	}
	else {
		title.setOutlineThickness(0);
		return false;
	}
}

void Buttons::ScreenScaleing(sf::Vector2f pos, float sizeX, float sizeY) {
	newScaleX = (sizeX - 1) + window.getSize().x / width;
	newScaleY = (sizeX - 1) + window.getSize().x / width;
	setScale(sf::Vector2f(newScaleX, newScaleY));
	setPosition(pos);
}

sf::Vector2f Buttons::getPosition() {
	return b.getPosition();
}

float Buttons::getNew() {
	return newScaleX;
}