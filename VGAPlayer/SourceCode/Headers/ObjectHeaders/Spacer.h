#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\Transform.hpp>

class Spacer
{
private:
	int temp;

public:
	sf::RectangleShape spacer;
	void SpacerObject(sf::RectangleShape &menu);
	int GetNumTemp();
	void SetNumTemp(int t);
};

