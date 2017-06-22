#pragma once

#include <sfeMovie\Movie.hpp>

class Movies {

public:
	void stop();
	void play();
	void pause();
	void drawVol(sf::RenderWindow &window, sf::Text &t1, sf::Text &t2);
	void drawShape(sf::RenderWindow &window, sf::RectangleShape &shape1, sf::RectangleShape &shape2);
	void drawMovie(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2);
	void drawMovieInv(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2);
	void updateMovies(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2);
	void movieTimers();
	void setVolume();
	void setMovieTimes();
};