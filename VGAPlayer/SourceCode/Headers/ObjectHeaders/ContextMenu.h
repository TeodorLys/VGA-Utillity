#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <vector>
#include "ContextMenuObjects.h"
class ContextMenu{
protected:
	float divBy;
	int forSave;
	int width = 0;
public:
	std::vector<textButton> objects;
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
	void addObject(textButton &t, std::string name);
	void objectsSetup();
};

