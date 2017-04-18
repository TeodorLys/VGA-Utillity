#include "ContextMenu.h"
#include "GlobalVariables.h"
#include "ContextMenuObjects.h"
#include <iostream>

using namespace std;
using namespace GV;

ContextMenu::ContextMenu() {
	divBy = 254.f / 34.f;
}

void ContextMenu::setup() {
	menu.setScale(1, 1);
	menu.setSize(sf::Vector2f(100,28));
	menu.setFillColor(sf::Color(242,242,242));
	menu.setOutlineColor(sf::Color(160,160,160));
	menu.setOutlineThickness(1.f);
	menu.setPosition((float)sfm.window.getSize().x / 2, (float)sfm.window.getSize().y / 2);
}

void ContextMenu::addObject(textButton &t, string name) {
	t.textObjects(divBy, name, menu);

	objects.push_back(t);
}

void ContextMenu::objectsSetup() {
	for (unsigned int a = 0; a < objects.size(); a++) {
		if (objects[a].t.getGlobalBounds().width > width) {
			width = (int)objects[a].t.getGlobalBounds().width;
		}
	}

	width = width * 3;

	if (width > 254) {
		width = 254;
	}

	menu.setSize(sf::Vector2f((float)width, 23.f * (float)objects.size() - (float)objects.size() + 9.f));

	for (unsigned int a = 0; a < objects.size(); a++) {
		objects[a].textRect.setSize(sf::Vector2f(menu.getSize().x - 4, 23));
	}

	spacer.setFillColor(sf::Color(145, 145, 145));
	spacer.setSize(sf::Vector2f(menu.getSize().x - 20, 1));
	spacer.setOrigin(spacer.getSize().x / 2, spacer.getSize().y / 2);
	spacer.setPosition(menu.getPosition().x + (menu.getSize().x / 2), objects[0].t.getPosition().y + 23);

}

void ContextMenu::setPosition() {
	menu.setPosition((float)sfm.mouse.getPosition(sfm.window).x, (float)sfm.mouse.getPosition(sfm.window).y);
	for (int a = 0; a < objects.size(); a++) {
		objects[a].t.setPosition(menu.getPosition().x + (menu.getSize().x / divBy), menu.getPosition().y + 8 + (22 * a - 1));
		objects[a].textRect.setPosition(menu.getPosition().x + 2, objects[a].t.getPosition().y - 3);
	}
	//spacer.setPosition(menu.getPosition().x + (menu.getSize().x / 2), about->t.getPosition().y + 23);
}

bool ContextMenu::isOver() {
	if (obj.actions.Hover(menu)) {
		return true;
	}
	else {
		return false;
	}
}

bool ContextMenu::showSelector() {
	for (unsigned int a = 0; a < objects.size(); a++) {
		if (obj.actions.Hover(objects[a].textRect)) {
			objects[a].textRect.setFillColor(sf::Color(217, 217, 217, 255));
			objects[a].textRect.setPosition(menu.getPosition().x + 2, objects[a].t.getPosition().y - 3);
			forSave = a;
		}
		else {
			objects[a].textRect.setFillColor(sf::Color(217, 217, 217, 0));
		}
	}
	if (forSave > 0 && forSave <= objects.size()) {
		if (objects[forSave].textRect.getFillColor() == sf::Color(217, 217, 217, 255)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void ContextMenu::draw() {
	sfm.window.draw(menu);
	for (unsigned int a = 0; a < objects.size(); a++) {
		sfm.window.draw(objects[a].textRect);
		sfm.window.draw(objects[a].t);
	}
	//sfm.window.draw(spacer);
}