#include "MovieEvents.h"
#include "MovieEvents\Multi.h"
#include "MovieEvents\Single.h"
#include "Objects\Buttons.h"
#include "Logger.h"
#include "DEBUG_Defines.h"
#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_Modules.h"

using namespace std;

void multiMovies::stop() {
 Shared_sfe::movie->stop();
 Shared_sfe::movie2->stop();
}

void multiMovies::play() {
 Shared_sfe::movie->play();
 Shared_sfe::movie2->play();
}

void multiMovies::pause() {
 Shared_sfe::movie->pause();
 Shared_sfe::movie2->pause();
}

void multiMovies::Draw_Text(sf::RenderWindow &window, sf::Text &t1, sf::Text &t2) {
 Shared_sf::window.draw(t1);
 Shared_sf::window.draw(t2);
}

void multiMovies::drawShape(sf::RenderWindow &window, sf::RectangleShape &shape1, sf::RectangleShape &shape2) {
 Shared_sf::window.draw(shape1);
 Shared_sf::window.draw(shape2);
}

void multiMovies::drawMovie(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
 if (Shared_bool::endOfSecondMovie) {
  Shared_Mod::secondReplay->draw();
 } else {
  Shared_sf::window.draw(mov2);
 }
 Shared_sf::window.draw(mov1);
}


void multiMovies::drawMovieInv(InitialSetup &initial ,sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
 Shared_sf::window.draw(mov1);

 if (Shared_bool::endOfSecondMovie)
  Shared_Mod::secondReplay->draw();
 else
  Shared_sf::window.draw(mov2);
}

void multiMovies::updateMovies(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
 Shared_sfe::movie->update();
 Shared_sfe::movie2->update();
}

void multiMovies::movieTimers(movieDuration &Duration) {
 Duration.Timer();
 Duration.smallTimer();
}

void multiMovies::setVolume(int first_Volume, float second_Volume) {
 Shared_sfe::movie->setVolume((float)first_Volume);
 Shared_sfe::movie2->setVolume((float)second_Volume);
}


void multiMovies::setMovieTimes() {
 Shared_sfe::movie->setPlayingOffset(sf::seconds(Shared_Var::mov1SaveTime));
 Shared_sfe::movie2->setPlayingOffset(sf::seconds(Shared_Var::mov2SaveTime));
 Shared_sf::off = sf::seconds(Shared_Var::mov2OffsetTime);
}


bool multiMovies::is_any_Movie_Paused() {
 if (Shared_sfe::movie->getStatus() == sfe::Status::Paused || 
	 Shared_sfe::movie2->getStatus() == sfe::Status::Paused) {
  return true;
 }
 else {
  return false;
 }
}


void singleMovies::stop() {
 Shared_sfe::movie->stop();
}

void singleMovies::play() {
 Shared_sfe::movie->play();
}

void singleMovies::pause() {
 Shared_sfe::movie->pause();
}

void singleMovies::Draw_Text(sf::RenderWindow &window, sf::Text &t1, sf::Text &t2) {
 Shared_sf::window.draw(t1);
}

void singleMovies::drawShape(sf::RenderWindow &window, sf::RectangleShape &shape1, sf::RectangleShape &shape2) {
 Shared_sf::window.draw(shape1);
}

void singleMovies::drawMovie(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
 Shared_sf::window.draw(mov1);
}

void singleMovies::drawMovieInv(InitialSetup &initial, sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
 Shared_sf::window.draw(mov1);
}

void singleMovies::updateMovies(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
 mov1.update();
}

void singleMovies::movieTimers(movieDuration &Duration) {
 Duration.Timer();
}

void singleMovies::setVolume(int first_Volume, float second_Volume) {
 Shared_sfe::movie->setVolume((float)first_Volume);
}

void singleMovies::setMovieTimes() {
 Shared_sfe::movie->setPlayingOffset(sf::seconds(Shared_Var::mov1SaveTime));
}

bool singleMovies::is_any_Movie_Paused() {
 if (Shared_sfe::movie->getStatus() == sfe::Status::Paused) {
  return true;
 }
 else {
  return false;
 }
}