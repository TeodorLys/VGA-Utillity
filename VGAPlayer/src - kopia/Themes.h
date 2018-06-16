#pragma once

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <vector>
#include <string>

class Themes
{
public:
	sf::Texture IconIMG;
	sf::Image bgIMG;
	bool bg;
	bool icon;
	int posX;
	int posY;
	std::vector<std::string> set;
	std::string IconSTR;
	std::string bgSTR;
	Themes();
	void setup();
};

