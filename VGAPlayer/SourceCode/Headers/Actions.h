#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class Actions {
private:
	int r;
	int g;
	int b;
	sf::Color c;
	bool doonce;
public:
	Actions();
	void highlight(sf::Text &t, std::string color, float thickness);
	void highlight(sf::RectangleShape &shape, std::string rcolor);
	bool Hover(sf::Text &t);
	bool Hover(sf::RectangleShape &shape);
	bool Hover(sf::Sprite &s);
	void deHightlight(sf::Text &t);
	void deHightlight(sf::RectangleShape &shape, sf::Color &c);
	bool Click();
	void reSync(sf::Time offset);
	bool movie2Hover();
	int ffstv();
	int lerp();
};

