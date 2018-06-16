#include "Menu_Handler.h"
#include <sfeMovie\Movie.hpp>
#include "Events\Animation.h"
#include "Events\Actions.h"
#include "Objects\Buttons.h"
#include "Objects\Switch.h"
#include "Events\Events.h"
#include "Audio.h"
#include "InitialSetup.h"
#include "Events\MovieEvents.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Modules.h"
#include "Shared\Shared_sfml_Objects.h"

using namespace std;

Menu_Handler::Menu_Handler(){}

/*--(Private Helper for Menu_Buttons)--*/
inline void Check_PLAY_Button(bool &can_Play, sfe::Movie &Movie_One, 
							  sfe::Movie &Movie_Two, size_t &Hour, 
							  size_t &Minute, size_t &Second, size_t &Small_Hour, 
							  size_t &Small_Minute, size_t &Small_Second, 
							  InitialSetup &initial, Audio &_audio, Events &Events_Object) {
 if (can_Play) {
  if (Shared_Mod::play->Hover(sf::Color(175, 175, 175), 2)) {
   if (Actions::Click() && !Shared_bool::doonce && !Shared_bool::mouseClick && Shared_bool::focus) {
	Events_Object.startMovies();

	_audio.Initialize_First_Movie_Timer(Movie_One, Hour, Minute, Second);

	if (Shared_Mod::oneMovie->switchON)
	 _audio.Initialize_Second_Movie_Timer(Movie_Two, Small_Hour, Small_Minute, Small_Second);

	Shared_bool::doonce = true;
   }
  }
 }
}

inline void Check_FFSTV_Button(InitialSetup &initial) {
 if (Shared_Mod::ffstv->Hover(sf::Color(175, 175, 175), 2)
	 && Actions::Click() && !Shared_bool::doonce && !Shared_bool::mouseClick && Shared_bool::focus) {
  initial.LoadMovie(1, &Shared_sfe::movie);
  Shared_bool::doonce = true;
 }
}

inline void Check_FILM_Button(InitialSetup &initial) {
 const float var = 14;
 if (Shared_Mod::oneMovie->switchON) {
  Shared_Mod::film->setTextColor(sf::Color(Animation::Lerp_Color(Shared_Mod::film->title.getFillColor(), sf::Color(255,125,0), var, var - 8, var, "TextColor")));
  Shared_Mod::film->outLine = sf::Color(Animation::Lerp_Color(Shared_Mod::film->outLine, sf::Color(255,125,0), var, var - 8, var, "Outline"));
  Shared_Mod::film->baseColor = sf::Color(Animation::Lerp_Color(Shared_Mod::film->baseColor, sf::Color(0,0,0), var, "BaseColor"));
  Shared_Mod::film->setButtonColor(5.5f);

  //User Clicks LOAD FILM Button.
  if (Shared_Mod::film->Hover(sf::Color(175, 175, 175), 2)
	  && Actions::Click() && !Shared_bool::doonce && !Shared_bool::mouseClick && Shared_bool::focus) {
   initial.LoadMovie(2, &Shared_sfe::movie2);
   Shared_bool::doonce = true;
  }

 }
 else {
  Shared_Mod::film->baseColor = sf::Color(Animation::Lerp_Color(Shared_Mod::film->baseColor, sf::Color(50, 50, 50), var, "BaseColor"));
  Shared_Mod::film->outLine = sf::Color(Animation::Lerp_Color(Shared_Mod::film->outLine, sf::Color(100,65,0), var, var - 8, var, "Outline"));
  Shared_Mod::film->setButtonColor(5.5f);
  Shared_Mod::film->setTextColor(sf::Color(Animation::Lerp_Color(Shared_Mod::film->title.getFillColor(), sf::Color(100,65,0), var, var - 8, var, "TextColor")));
 }
}
/*--(Private Helper for Menu_Buttons)--*/

void Menu_Handler::Menu_Buttons(sfe::Movie &Movie_One, sfe::Movie &Movie_Two,
							 InitialSetup &initial, Audio &_audio, Events &Events_Object) {

 Check_PLAY_Button(can_Play, Movie_One, Movie_Two, Shared_Var::hour, Shared_Var::minute, 
				   Shared_Var::second, Shared_Var::smallhour, Shared_Var::smallminute, 
				   Shared_Var::smallsecond, initial, _audio, Events_Object);
 Check_FILM_Button(initial);
 Check_FFSTV_Button(initial);
 Empty_Path(initial);
}

void Menu_Handler::Empty_Path(InitialSetup &initial) {
 if (initial.ffs != "NONE" && initial.mov != "NONE" || initial.ffs != "NONE" && !Shared_Mod::oneMovie->switchON) {
  Shared_Mod::play->baseColor = sf::Color(0, 0, 0);
  Shared_Mod::play->outLine = sf::Color(255, 125, 0);
  Shared_Mod::play->setButtonColor(5.5f);
  Shared_Mod::play->setTextColor(sf::Color(255, 125, 0));

  can_Play = true;
 }
}


void Menu_Handler::Replay_Movies(sfe::Movie &Movie_One, movBase &Movie_Events_Object) {
 Movie_Events_Object.stop();
 Shared_bool::endOfMovie = false;
 Shared_bool::movie_is_Playing = true;
 Shared_bool::doonce = true;
 Movie_One.play();
}


void Menu_Handler::End_Screen(bool &get_Doonce, sfe::Movie &Movie_One, InitialSetup &initial, movBase &Movie_Object) {
 if (Shared_Mod::replay->Hover(sf::Color(175, 175, 175), 2))
  Actions::Click() && !get_Doonce ? Replay_Movies(Movie_One, Movie_Object) : 0;
 else if (Shared_Mod::ret->Hover(sf::Color(175, 175, 175), 2))
  Actions::Click() && !get_Doonce ? Return_To_Menu(Movie_Object) : 0;
}

void Menu_Handler::set_Info_Opacity(sf::Uint8 alphaColor) {
 Shared_sf::vol1.setFillColor(sf::Color(Shared_sf::vol1.getFillColor().r, Shared_sf::vol1.getFillColor().g, Shared_sf::vol1.getFillColor().b, alphaColor));
 Shared_sf::vol2.setFillColor(sf::Color(Shared_sf::vol2.getFillColor().r, Shared_sf::vol2.getFillColor().g, Shared_sf::vol2.getFillColor().b, alphaColor));
 Shared_sf::smalltTimer.setFillColor(sf::Color(Shared_sf::smalltTimer.getFillColor().r, Shared_sf::smalltTimer.getFillColor().g, Shared_sf::smalltTimer.getFillColor().b, alphaColor));
 Shared_sf::tTimer.setFillColor(sf::Color(Shared_sf::tTimer.getFillColor().r, Shared_sf::tTimer.getFillColor().g, Shared_sf::tTimer.getFillColor().b, alphaColor));
}

void Menu_Handler::Return_To_Menu(movBase &Movie_Events_Object) {
 Movie_Events_Object.stop();
 Shared_bool::menu_Is_Shown = true;
 Shared_bool::endOfMovie = false;
 Shared_bool::movie_is_Playing = false;
 Shared_bool::doonce = true;
}