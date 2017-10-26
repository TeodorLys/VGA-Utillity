#pragma once
#include "InitialSetup.h"
#include "Events\movieDuration.h"
#include "Events\MovieEvents.h"
#include "Audio.h"

class multiMovies : public movBase {
public:
 multiMovies(){}
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
  printf("Testmuilti\n");
 }
};