#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <vector>
#include "ContextMenuObjects.h"
#include "Spacer.h"

class ContextMenu{
protected:
	float divBy;
	bool hasSpacer = false;
	int forSave;
	int width = 0;
	int spacerIndex;
	int addedstuff = 0;
	int spacerPosIndex = 0; 
public:
	std::vector<textButton> objects;
	std::vector<Spacer> spaceObjects;
	sf::RectangleShape menu;
	sf::RectangleShape select;
	sf::RectangleShape spacer;
	bool contextMenuShown = false;
	ContextMenu();
	void setup();
	void draw();
	void setPosition();
	bool isOver();
	bool showSelector();
	void addObject(textButton &t, std::string name); //For text objects
	void addObject(Spacer &space, int spacer);   //For spacer Objects
	void objectsSetup();
	int GetIndex(std::string wN);
};

