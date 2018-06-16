
#include "ContextMenuObjects.h"
#include <string>

void textButton::textObjects(float divBy, std::string str, sf::RectangleShape &base, sf::Font &sys) {
	t.setFont(sys);
	t.setStyle(sf::Text::Regular);
	t.setCharacterSize(13);
	t.setScale(0.95f, 0.9f);
	t.setPosition(base.getPosition().x + (base.getSize().x / divBy), base.getPosition().y + 8);
	t.setString(str);
	t.setFillColor(sf::Color(0, 0, 0));

	textRect.setSize(sf::Vector2f(base.getSize().x - 4, 23));
	textRect.setFillColor(sf::Color(217, 217, 217, 0));
	textRect.setPosition(base.getPosition().x + 2, t.getPosition().y - 3);
}

std::string textButton::getName() {
	return t.getString();
}

void textButton::setColor(sf::Color c) {
 t.setFillColor(c);
}