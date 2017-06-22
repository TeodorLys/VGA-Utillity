#pragma once

#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Time.hpp>
#include <string>

class Actions {
private:
	int r;
	int g;
	int b;
	sf::Color c;
	bool doonce;
public:
	float xLimit = 0;
	float yLimit = 0;
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
	void SetLimits(float LX, float LY);
};

