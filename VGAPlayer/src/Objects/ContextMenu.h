#pragma once
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <string>
#include "ContextMenuObjects.h"
#include "Spacer.h"

class textButton;
class Spacer;

class ContextMenu{
public:
 std::vector<textButton> objects;
 std::vector<Spacer> spaceObjects;
 sf::RectangleShape menu;
 sf::RectangleShape select;
 sf::RectangleShape spacer;
 bool contextMenuShown = false;
protected:
	float divBy;
	bool hasSpacer = false;
	int forSave;
	int width = 0;
	int spacerIndex;
	int addedstuff = 0;
	int spacerPosIndex = 0; 
public:
	ContextMenu();
	void setup();
	void draw(sf::RenderWindow &window);
	void setPosition(sf::RenderWindow &window, sf::Mouse &mouse);
	bool isOver();
	bool showSelector();

	void addObject(textButton &t, std::string name, sf::Font &sys); //For text objects
	void addObject(Spacer &space, int spacer);   //For spacer Objects
	void addObject(textButton &t, std::string name, sf::Font &sys, sf::Color c);
	
	void objectsSetup();
	int GetIndex(std::string wN);
};

