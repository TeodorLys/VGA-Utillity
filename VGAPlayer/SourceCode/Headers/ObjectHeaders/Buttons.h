#pragma once
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Transform.hpp>
#include <string>
class Buttons
{
private:
	sf::Text title;
	void rectangle();
	float HeightAdd;
	float WidthAdd;
public:
	sf::RectangleShape b;
	Buttons();
	float newScaleX;
	float newScaleY;
	void setText(std::string str);
	void draw();
	void setScale(sf::Vector2f vec);
	void setTextColor(sf::Color c);
	void setButtonColor(sf::Color c, sf::Color outline, float line);
	void setPosition(sf::Vector2f pos, float extra);
	void setSize(float h, float w);
	bool Hover(sf::Color c, float size);
	void ScreenScaleing(sf::Vector2f pos, float sizeX, float sizeY, float extra);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	float getNew();
};

