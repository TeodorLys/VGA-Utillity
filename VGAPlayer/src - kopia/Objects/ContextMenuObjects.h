#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Color.hpp>

class textButton {
public:
 sf::Text t;
 sf::RectangleShape textRect;
 bool isActive = true;
public:
	void textObjects(float divBy, std::string str, sf::RectangleShape &base, sf::Font &sys);
	std::string getName();
	void setColor(sf::Color c);
};