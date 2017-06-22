#pragma once
class Debugging
{
public:
	std::string value = "0.00";
	float convValue = 0;
	bool writing = false;
	sf::Text write;
	sf::RectangleShape bg;
	Debugging();
	void valueField();
	void draw();
};

