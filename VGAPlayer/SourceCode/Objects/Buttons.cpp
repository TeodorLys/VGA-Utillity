#include "Buttons.h"
#include "GlobalVariables.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace GV;

Buttons::Buttons(){
	newScaleX = 0;
	newScaleY = 0;
}

//Sets the initial settings for the text inside the button
void Buttons::setText(string str) {
	//All of this is sf::Text
	title.setString(str);    //Sets the string of the text
	title.setFont(sfm.font);   //Sets the font 
	title.setCharacterSize(32);   //Sets the font size
	title.setStyle(sf::Text::Regular);   //Sets the style, in this case regular
	title.setScale(1, 1);   //Initial scale, will be changed later
	rectangle();   //Fires the rectangle function

	//Sets the origin point, in this case, the middle of the text
	title.setOrigin(sf::Vector2f(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2));
}

//Sets the scale of both the text and button
void Buttons::setScale(sf::Vector2f vec) {
	title.setScale(vec);
	//Sets the scale of the button based on the text
	b.setSize(sf::Vector2f(title.getGlobalBounds().width + WidthAdd, title.getGlobalBounds().height + HeightAdd));
	//And the origin, dont know why, but this had to be done
	b.setOrigin(sf::Vector2f(b.getSize().x / 2, b.getSize().y / 2));
}

//Sets the wanted color of the text
void Buttons::setTextColor(sf::Color c) {
	title.setFillColor(c);
}

//Sets the button base color, and outline color and thickness
void Buttons::setButtonColor(sf::Color c, sf::Color outline, float line) {
	b.setFillColor(c);
	b.setOutlineColor(outline);
	b.setOutlineThickness(line);
}

//Draws both the button and the text
void Buttons::draw() {
	sfm.window.draw(b);
	sfm.window.draw(title);
}

//Base button settings
void Buttons::rectangle() {
	//Sets the initial size of the button, will be changed later
	b.setSize(sf::Vector2f(title.getGlobalBounds().width + WidthAdd, title.getGlobalBounds().height + HeightAdd));
	//And the origin, in this case, in the middle of the button
	b.setOrigin(sf::Vector2f(b.getSize().x / 2, b.getSize().y / 2));
}

//Sets the extra size of the button: How much beyond the text bounds
void Buttons::setSize(float h, float w) {
	HeightAdd = h;
	WidthAdd = w;
}

//Sets the position on the button
void Buttons::setPosition(sf::Vector2f pos, float extra) {
	b.setPosition(pos);
	//And in this case the text will be set Dependant on the button position
	title.setPosition(b.getPosition().x, b.getPosition().y - extra);	
}

//If the mouse hovers over the button
bool Buttons::Hover(sf::Color c, float size) {
	if (b.getGlobalBounds().contains(sf::Vector2f(sfm.mouse.getPosition(sfm.window)))) {
		title.setOutlineColor(c);  //Change the outline color of the text
		title.setOutlineThickness(size);   //And the thickness, Original: 0
		return true;
	}
	else {
		title.setOutlineThickness(0);
		return false;
	}
}

//Function to, globally, change the scaling from the window resize
void Buttons::ScreenScaleing(sf::Vector2f pos, float sizeX, float sizeY, float extra) {
	newScaleX = (sizeX - 1) + sfm.window.getSize().x / value.width;
	newScaleY = (sizeX - 1) + sfm.window.getSize().x / value.width;
	setScale(sf::Vector2f(newScaleX, newScaleY));
	setPosition(pos, extra);
}

//Returns the position of the button, in sf::Vector float form
sf::Vector2f Buttons::getPosition() {
	return b.getPosition();
}

sf::Vector2f Buttons::getSize() {
	return b.getSize();
}

//Returns the new scale, from the window resize/ScreenScaleing function
float Buttons::getNew() {
	return newScaleX;
}
