#include "ContextMenu.h"
#include "GlobalVariables.h"
#include "ContextMenuObjects.h"
#include "Spacer.h"
#include <iostream>

using namespace std;
using namespace GV;

ContextMenu::ContextMenu() {
	divBy = 254.f / 34.f;
	forSave = 0; 
	spacerIndex = 0;
}

void ContextMenu::setup() {
	menu.setScale(1, 1);
	menu.setSize(sf::Vector2f(100,28));   //Sets the default size, will change later
	menu.setFillColor(sf::Color(242,242,242));   //Sets the background color
	menu.setOutlineColor(sf::Color(160,160,160));   //Sets the outline color
	menu.setOutlineThickness(1.f);
	menu.setPosition((float)sfm.window.getSize().x / 2, (float)sfm.window.getSize().y / 2);   //Sets the pos based on the window size
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// \Adds the different text objects to a vector, so										 ///
/// \you can access it with ease                                                             ///
////////////////////////////////////////////////////////////////////////////////////////////////
void ContextMenu::addObject(textButton &t, string name) {
	t.textObjects(divBy, name, menu);
	objects.push_back(t);
	spacerIndex++;
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// Overloaded function of the above														 ///
////////////////////////////////////////////////////////////////////////////////////////////////
void ContextMenu::addObject(Spacer &space, int spacer) {
	if (spacer == 42) {
		space.SpacerObject(menu);
		space.SetNumTemp((spacerIndex - 1));
		spaceObjects.push_back(space);
		hasSpacer = true;
	}
	else {
		return;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////
///Sets up all of the text objects
///And bases the context box based on the longest text
////////////////////////////////////////////////////////////////////////////////////////////////
void ContextMenu::objectsSetup() {
	//Finds the longest text and saves it
	for (unsigned int a = 0; a < objects.size(); a++) {
		if (objects[a].t.getGlobalBounds().width > width) {
			width = (int)objects[a].t.getGlobalBounds().width;
		}
	}

	width = width * 3;   //Multiplys by 3, because... reasons

	//Absolute Size of Context Box
	if (width > 254) {
		width = 254;
	}

	menu.setSize(sf::Vector2f((float)width, 23.f * (float)objects.size() - (float)objects.size() + 9.f + spaceObjects.size() * 8));

	for (unsigned int a = 0; a < objects.size(); a++) {
		objects[a].textRect.setSize(sf::Vector2f(menu.getSize().x - 4, 23));
	}

	for (unsigned int a = 0; a < spaceObjects.size(); a++) {
		spaceObjects[a].spacer.setSize(sf::Vector2f(menu.getSize().x - 20, 1));
		spaceObjects[a].spacer.setOrigin(spaceObjects[a].spacer.getSize().x / 2, spaceObjects[a].spacer.getSize().y / 2);
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////
///Sets the position based on the mouse position																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void ContextMenu::setPosition() {
	//Sets the Context box
	menu.setPosition((float)sfm.mouse.getPosition(sfm.window).x, (float)sfm.mouse.getPosition(sfm.window).y);

	//Sets the Text within the Context Box
	for (int a = 0; a < ((int)objects.size() + (int)spaceObjects.size()); a++) {
		if (hasSpacer) {
				objects[a].t.setPosition(menu.getPosition().x + (menu.getSize().x / divBy), menu.getPosition().y + 8 + (22 * a - 1) + addedstuff);
				objects[a].textRect.setPosition(menu.getPosition().x + 2, objects[a].t.getPosition().y - 3);

			if (a == spaceObjects[spacerPosIndex].GetNumTemp()) {
				spaceObjects[spacerPosIndex].spacer.setPosition(menu.getPosition().x + (menu.getSize().x / 2), objects[a].t.getPosition().y + 23);
				addedstuff += 8;
				spacerPosIndex++;
			}
		}
		else {
			objects[a].t.setPosition(menu.getPosition().x + (menu.getSize().x / divBy), menu.getPosition().y + 8 + (22 * a - 1));
			objects[a].textRect.setPosition(menu.getPosition().x + 2, objects[a].t.getPosition().y - 3);
		}
	}
	spacerPosIndex = 0;
	addedstuff = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////
///If mouse is over the currently shown Context Box
////////////////////////////////////////////////////////////////////////////////////////////////
bool ContextMenu::isOver() {
	if (obj.actions.Hover(menu)) {
		return true;
	}
	else {
		return false;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////
///Gets which Text object the mouse hovers over															 
////////////////////////////////////////////////////////////////////////////////////////////////
bool ContextMenu::showSelector() {
	//First of all, find where the mouse is and if it is over any of the text object
	//Change that text objects rectangle color to "Selected"
	for (unsigned int a = 0; a < objects.size(); a++) {
		if (obj.actions.Hover(objects[a].textRect)) {
			objects[a].textRect.setFillColor(sf::Color(217, 217, 217, 255));
			objects[a].textRect.setPosition(menu.getPosition().x + 2, objects[a].t.getPosition().y - 3);
			//Second of all save the index of the selected text object
			forSave = a;
		}
		//Otherwise change all back the selected text object to... unselected
		else {
			objects[a].textRect.setFillColor(sf::Color(217, 217, 217, 0));
		}
	}

	//Return true if any text object is selected
	if (forSave >= 0 && forSave <= (int)objects.size()) {
		if (objects[forSave].textRect.getFillColor() == sf::Color(217, 217, 217, 255)) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
///Draw the context box, and accompanied text objects																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void ContextMenu::draw() {
	sfm.window.draw(menu);
	for (unsigned int a = 0; a < objects.size(); a++) {
		sfm.window.draw(objects[a].textRect);
		sfm.window.draw(objects[a].t);

		if (hasSpacer) {
			if (a < spaceObjects.size()) {
				sfm.window.draw(spaceObjects[a].spacer);
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////
///Gets the index of the clicked text object																			 
////////////////////////////////////////////////////////////////////////////////////////////////
int ContextMenu::GetIndex(std::string wN) {
	for (unsigned int a = 0; a < objects.size(); a++) {
		if (wN == objects[a].t.getString()) {
			return a;
		}
	}
	return 0;
}