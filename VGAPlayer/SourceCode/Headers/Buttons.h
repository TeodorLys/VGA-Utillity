#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Buttons
{
private:
	sf::Text title;
	sf::RectangleShape b;
	void rectangle();
	float HeightAdd;
	float WidthAdd;
public:
	Buttons();
	~Buttons();
	float newScaleX;
	float newScaleY;
	void setText(std::string str);
	void draw();
	void setScale(sf::Vector2f vec);
	void setTextColor(sf::Color c);
	void setButtonColor(sf::Color c, sf::Color outline, float line);
	void setPosition(sf::Vector2f pos);
	void setSize(float h, float w);
	bool Hover(sf::Color c, float size);
	void ScreenScaleing(sf::Vector2f pos, float sizeX, float sizeY);
	sf::Vector2f getPosition();
	float getNew();
};

