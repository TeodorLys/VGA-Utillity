#pragma once
#include <sfeMovie\Movie.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>

class movieDuration;
class InitialSetup;

class movBase {
public:
 virtual void stop() {}
 virtual void play() {}
 virtual void pause() {}
 virtual void Draw_Text(sf::RenderWindow &window, sf::Text &t1, sf::Text &t2) {}
 virtual void drawShape(sf::RenderWindow &window, sf::RectangleShape &shape1, sf::RectangleShape &shape2) {}
 virtual void drawMovie(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {}
 virtual void drawMovieInv(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {}
 virtual void updateMovies(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {}
 virtual void movieTimers(movieDuration &Duration) {}
 virtual void setVolume(int first_Volume, float second_Volume) {}
 virtual void setMovieTimes() {}
 virtual bool is_any_Movie_Paused() { return false; }
 virtual void t() {}
};