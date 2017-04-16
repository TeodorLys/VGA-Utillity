#pragma once

#include "Events.h"

class keyPress : public Events
{
public:
	void press(sf::Event event, sf::Time time);
};

