#pragma once

#include "Events\MovieEvents.h"

class singleMovies : public movBase {
public:
	singleMovies(){}
	void stop();
	void play();
	void pause();
	void Draw_Text(sf::Text &t1, sf::Text &t2);
	void drawShape(sf::RectangleShape &shape1, sf::RectangleShape &shape2);
	void drawMovie(sfe::Movie &mov1, sfe::Movie &mov2);
	void drawMovieInv(sfe::Movie &mov1, sfe::Movie &mov2);
	void updateMovies(sfe::Movie &mov1, sfe::Movie &mov2);
	void movieTimers(movieDuration &Duration);
	void setVolume(int first_Volume, float second_Volume);
	void setMovieTimes();
	bool is_any_Movie_Paused();
	void t() {
	 printf("Test Single\n");
	}
};