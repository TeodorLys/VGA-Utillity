#pragma once

#include <SFML\Graphics.hpp>

class Events {

protected:
	void startMovies();

	void enterFullscreen(sf::RenderWindow &window);
	void exitFullscreen(sf::RenderWindow &window);

public:
	void checkKeypress(sf::Event event, sf::Time time);
	void SaveSettings();
};
