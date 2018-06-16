#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
class Spacer
{
private:
	int temp = 0;
public:
	sf::RectangleShape spacer;
	void SpacerObject(sf::RectangleShape &menu);
	int GetNumTemp();
	void SetNumTemp(int t);
};

