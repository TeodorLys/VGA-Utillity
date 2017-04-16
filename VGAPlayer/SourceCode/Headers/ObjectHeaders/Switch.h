#pragma once
#include <SFML\Graphics.hpp>
class Switch {

private:

	sf::RectangleShape base;
	sf::RectangleShape swit;

public:
	Switch();
	bool switchON = true;
	void draw();
	void setBase();
	void setSwitch();
	void setScale(sf::Vector2f scale);
	bool clickSwitch();
	void setPosition(sf::Vector2f pos);
	
};

