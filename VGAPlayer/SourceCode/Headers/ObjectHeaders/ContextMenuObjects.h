#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <string>

class textButton {

public:
	sf::Text t;
	sf::RectangleShape textRect;
	void textObjects(float divBy, std::string str, sf::RectangleShape &base);
};