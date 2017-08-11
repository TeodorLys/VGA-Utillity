#pragma once

#include "Events\MovieEvents.h"

class singleMovies : public movBase {
public:
	singleMovies(){}
	void stop();
	void play();
	void pause();
	void Draw_Text(sf::RenderWindow &window, sf::Text &t1, sf::Text &t2);
	void drawShape(sf::RenderWindow &window, sf::RectangleShape &shape1, sf::RectangleShape &shape2);
	void drawMovie(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2);
	void drawMovieInv(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2);
	void updateMovies(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2);
	void movieTimers(movieDuration &Duration);
	void setVolume(int first_Volume, float second_Volume);
	void setMovieTimes();
	bool is_any_Movie_Paused();
	void t() {
	 printf("Test Single\n");
	}
};