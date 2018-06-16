#pragma once
#include <sfeMovie\Movie.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <mutex>

class movieDuration;
class InitialSetup;

class movBase {
public:
	std::mutex m;
 virtual void stop() {}
 virtual void play() {}
 virtual void pause() {}
 virtual void Draw_Text(sf::Text &t1, sf::Text &t2) {}
 virtual void drawShape(sf::RectangleShape &shape1, sf::RectangleShape &shape2) {}
 virtual void drawMovie(sfe::Movie &mov1, sfe::Movie &mov2) {}
 virtual void drawMovieInv(sfe::Movie &mov1, sfe::Movie &mov2) {}
 virtual void updateMovies(sfe::Movie &mov1, sfe::Movie &mov2) {}
 virtual void movieTimers(movieDuration &Duration) {}
 virtual void setVolume(int first_Volume, float second_Volume) {}
 virtual void setMovieTimes() {}
 virtual bool is_any_Movie_Paused() { return false; }
 virtual void t() {}
};