#include "Spacer.h"

using namespace std;

void Spacer::SpacerObject(sf::RectangleShape &menu) {
	spacer.setFillColor(sf::Color(145, 145, 145));
	spacer.setSize(sf::Vector2f(menu.getSize().x - 20, 1));
	spacer.setOrigin(spacer.getSize().x / 2, spacer.getSize().y / 2);
}

int Spacer::GetNumTemp() {
	return temp;
}

void Spacer::SetNumTemp(int t) {
	temp = t;
}