#include "keyPress.h"
#include "Events.h"
#include "MovieEvents.h"
#include "Objects\Switch.h"
#include "Write_Field.h"
#include "Logger.h"
#include "Debugging.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_Modules.h"

using namespace std;

keyPress::keyPress(Events* event, movBase** mov, Debugging *Debug_Object) : ev(event), movie(mov), debug(Debug_Object){}

void keyPress::press(sf::Event event) {

 switch (event.key.code) {
  ///If the user clicks SPACE
 case sf::Keyboard::Space:
 ///Checks if the movie is playing
  if (Shared_bool::movie_is_Playing) {
   Shared_bool::movie_Status_Changed = true;
   if (Shared_sfe::movie->getStatus() == sfe::Playing) {
	//Pauses the movies if it is playing
	Shared_sfe::movie->pause();

	Shared_Mod::oneMovie->switchON && Shared_bool::movie2Active ? Shared_sfe::movie2->pause() : 0;
   }
   else {
	//If the movie isnt playing, play them
	Shared_sfe::movie->play();
	Shared_Mod::oneMovie->switchON && Shared_bool::movie2Active ? Shared_sfe::movie2->play() : 0;
   }
  }

 break;
 ///If the user clicks the 'F' key
 case sf::Keyboard::F:
 if (!Shared_bool::isFullscreen) {
  ev->enterFullscreen(Shared_sf::window);
  Shared_bool::isFullscreen = true;
 } 
 else {
  ev->exitFullscreen(Shared_sf::window);
  Shared_bool::isFullscreen = false;
 }
 break;

 case sf::Keyboard::Right:
 //gets the current playing time
  if (Shared_bool::movie_is_Playing) {
   time = sf::seconds(Shared_sfe::movie->getPlayingOffset().asSeconds());

   if (Shared_sfe::movie->getDuration().asSeconds() - Shared_sfe::movie->getPlayingOffset().asSeconds() < 10)
	Shared_Var::inc = time.asSeconds() + (Shared_sfe::movie->getDuration().asSeconds() - Shared_sfe::movie->getPlayingOffset().asSeconds() - 1);
   else
	Shared_Var::inc = time.asSeconds() + 10;

   if (Shared_Mod::oneMovie->switchON) {
	if (Shared_sfe::movie2->getDuration().asSeconds() - Shared_sfe::movie2->getPlayingOffset().asSeconds() < 10)
	 Shared_Var::secondInc = time.asSeconds() + (Shared_sfe::movie2->getDuration().asSeconds() - Shared_sfe::movie2->getPlayingOffset().asSeconds() - 1);
	else
	 Shared_Var::secondInc = time.asSeconds() + 10;
   }

   (**movie).pause();
   Shared_sfe::movie->setPlayingOffset(sf::seconds(Shared_Var::inc));

   //Moves forward in the smaller movie with 10 seconds
   Shared_Mod::oneMovie->switchON ?
	Shared_sfe::movie2->setPlayingOffset(sf::seconds(Shared_Var::secondInc) - Shared_sf::off) : 0;

   (**movie).play();
  }
 break;

 ///If user clicks the left arrow button
 if (Shared_bool::movie_is_Playing) {
 case sf::Keyboard::Left:
  time = sf::seconds(Shared_sfe::movie->getPlayingOffset().asSeconds());

  (**movie).pause();
  if (Shared_sfe::movie->setPlayingOffset(time - sf::seconds(10)))
   print.Log_Info("New Playin offset1: %f", time.asSeconds() - 10);
  else
   print.Log_Warning("Setting playing offset Failed!");

  if (Shared_Mod::oneMovie->switchON) {
   Shared_sfe::movie2->setPlayingOffset(time - sf::seconds(10) - Shared_sf::off);
   print.Log_Info("New Playin offset1: %i", (time.asSeconds() - 10 - Shared_sf::off.asSeconds()));
  }
  else
   print.Log_Warning("Setting playing offset of Movie2 Failed!");

  (**movie).play();
 }
 break;

 case sf::Keyboard::E:
  if(Shared_Mod::oneMovie->switchON){ 
   Shared_sfe::movie2->getStatus() == sfe::Playing ? Shared_sfe::movie2->pause() : Shared_sfe::movie2->play(); 
  }
 
 break;

 case sf::Keyboard::Q:
  Shared_bool::movie_Status_Changed = true;
 Shared_sfe::movie->getStatus() == sfe::Playing ? Shared_sfe::movie->pause() : Shared_sfe::movie->play();
 break;

 case sf::Keyboard::G:
 syncMovie();
 break;

 case sf::Keyboard::LAlt:
 !Shared_bool::behind ? Shared_bool::behind = true : Shared_bool::behind = false;
 break;

 case sf::Keyboard::K:
 Shared_sfe::movie2->stop();
 syncMovie();

 case sf::Keyboard::J:
  Write_Field::write().setPosition(Shared_sf::window.getSize().x - (Write_Field::write().getSize().x + (Write_Field::write().getSize().x / 8)),
								   Shared_sf::window.getSize().y - (Write_Field::write().getSize().y + (Write_Field::write().getSize().y / 8)));
  Write_Field::write().is_Writing = true;
  break;
 case sf::Keyboard::Escape:
  if (Shared_bool::isFullscreen) {
   ev->exitFullscreen(Shared_sf::window);
  }
  break;

 case sf::Keyboard::D:
  debug->setPosition(sf::Vector2f(5, (float)Shared_sf::window.getSize().y / 2));
  debug->writing = true;
  break;

 default:
 break;
 }
}


inline void keyPress::syncMovie() {
 Shared_sf::off = Shared_sfe::movie->getPlayingOffset();
 if (Shared_Mod::oneMovie->switchON) {
  if (Shared_sfe::movie2->getStatus() != sfe::Playing) {
   Shared_sfe::movie2->play();
   Shared_bool::movie2Active = true;
  }
 }
}

