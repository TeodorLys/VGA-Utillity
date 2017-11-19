#pragma once
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>

class Buttons
{
private:

	void rectangle();
	float HeightAdd;
	float WidthAdd;
public:
	bool *focus;
	sf::Text title;
	sf::Color outLine = sf::Color(255, 125, 0);
	sf::Color baseColor = sf::Color(0, 0, 0);
	
	sf::RenderWindow *window;
	sf::Mouse *mouse;
	sf::Font *font;

	sf::RectangleShape b;
	Buttons(sf::RenderWindow *w, sf::Mouse *m, sf::Font *f, bool *fo);
	~Buttons();
	float newScaleX = 0;
	float newScaleY = 0;
	void setText(std::string str);
	void draw();
	void setScale(sf::Vector2f vec);
	void setTextColor(sf::Color c);
	void setButtonColor(float line);
	void setPosition(sf::Vector2f pos, float extra);
	void setSize(float h, float w);
	bool Hover(sf::Color c, float size);
	void ScreenScaleing(sf::Vector2f pos, float sizeX, float sizeY, float extra);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	float getNew();
};

