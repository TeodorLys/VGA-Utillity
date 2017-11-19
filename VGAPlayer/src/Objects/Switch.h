#pragma once
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
//#include "Actions.h"
class Switch {
private:
	sf::RectangleShape base;
	sf::RectangleShape swit;
	sf::Mouse *mouse;
	sf::RenderWindow *window;
	bool *focus;
	//Actions *action;
public:
	Switch(bool &f, sf::Mouse &m, sf::RenderWindow &w/*, Actions &a*/);
	~Switch();
	bool switchON = true;
	void draw();
	void setBase();
	void setSwitch();
	void setScale(sf::Vector2f scale);
	bool clickSwitch();
	void setPosition(sf::Vector2f pos);
	
};

