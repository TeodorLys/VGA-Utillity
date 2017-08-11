#include "Events.h"
#include <Windows.h>
#include "keyPress.h"
#include "Resized.h"
#include "InitialSetup.h"
#include "MovieEvents.h"
#include "Audio.h"
#include "Objects\Switch.h"
#include "Objects\Buttons.h"
#include "Save\Save_Files.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_String.h"
#include "Shared\Shared_SaveVariables.h"
#include "Shared\Shared_Modules.h"

using namespace std;

Events::Events(keyPress* key, Resized* res, InitialSetup* is, mouseEvent* mou, movBase** mov, Audio *audio_Object) : 
			   kp(key), re(res), initial(is), me(mou), movie(mov), _audio(audio_Object){}


void Events::checkKeypress(sf::Event event) {
 if (event.type == sf::Event::KeyPressed) {
  kp->press(event);
 }
 else if (event.type == sf::Event::Resized || changeStyle) {
  Shared_bool::movie_is_Playing? re->playResize() : re->menuResize();
  Shared_sf::window.setView(sf::View(sf::FloatRect(0, 0, (float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y)));
  initial->Movie2Limits();
  changeStyle = false;
 }

 else if (event.type == sf::Event::MouseWheelMoved) {
   if (Shared_bool::movie_is_Playing) {
	_audio->set_Volume_at_Runtime();
   }
 }//Mouse wheel moved END 
}//Poll event END


///Sets the window in BORDERLESS fullscreen mode
void Events::enterFullscreen(sf::RenderWindow &window) {
 WINDOWPLACEMENT pl;
 GetWindowPlacement(Shared_sf::window.getSystemHandle(), &pl);
 switch (pl.flags) {
 case 0:
  Shared_bool::Maximized_on_Exit_Fullscreen = false;
  break;
 case 2:
  Shared_bool::Maximized_on_Exit_Fullscreen = true;
  break;
 }

 newWidth = (float)window.getSize().x;
 newHeight = (float)window.getSize().y;
 window_Pos_X = window.getPosition().x;
 window_Pos_Y = window.getPosition().y;

 LONG style = GetWindowLong(window.getSystemHandle(), GWL_STYLE);
 saved_Style = style;
 style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
 SetWindowLong(window.getSystemHandle(), GWL_STYLE, style);

 ShowWindow(Shared_sf::window.getSystemHandle(), SW_MAXIMIZE);

 Shared_bool::isFullscreen = true;
 changeStyle = true;
}


///Exits the BORDERLESS fullscreen 
void Events::exitFullscreen(sf::RenderWindow &window) {
 SetWindowLong(window.getSystemHandle(), GWL_STYLE, saved_Style);

 Shared_bool::isFullscreen = false;
 changeStyle = true;

 window.setPosition(sf::Vector2i(window_Pos_X, window_Pos_Y));

 if (Shared_bool::Maximized_on_Exit_Fullscreen)
  ShowWindow(Shared_sf::window.getSystemHandle(), SW_MAXIMIZE);
 else
  ShowWindow(Shared_sf::window.getSystemHandle(), SW_RESTORE);
}


///Runs all of the setup for the movies
void Events::startMovies() {
	Shared_bool::movie_is_Playing = true;
	Shared_sfe::movie->fit(0, 0, Shared_Var::w, Shared_Var::h);
	Shared_sfe::movie->play();
	
	Shared_sf::window.setSize(sf::Vector2u((unsigned int)Shared_Var::w, (unsigned int)Shared_Var::h));
	Shared_sf::window.setView(sf::View(sf::FloatRect(0, 0, (float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y)));
	Shared_sf::vol2.setPosition(Shared_sf::window.getSize().x - 60.f, 25);

	Shared_sf::tTimer.setPosition(0, Shared_sf::window.getSize().y - Shared_sf::tTimer.getGlobalBounds().height);
	Shared_Mod::oneMovie->switchON ?
		Shared_sf::smalltTimer.setPosition(Shared_sf::window.getSize().x - Shared_sf::smalltTimer.getGlobalBounds().width - 20,
										  Shared_sf::window.getSize().y - Shared_sf::smalltTimer.getGlobalBounds().height),
										  Shared_Mod::secondReplay->setPosition(sf::Vector2f(Shared_sfe::movie2->getPosition().x, 0), 5) : 0;
	re->playMenuResize();
	Shared_sf::window.setActive(false);

	Shared_sf::vol1.setString(to_string(_audio->first_Mov_Vol));
	Shared_sf::vol2.setString(to_string((int)_audio->second_Mov_Vol));

	(**movie).setVolume(_audio->first_Mov_Vol, _audio->second_Mov_Vol);

	(**movie).setMovieTimes();
	Shared_Mod::oneMovie->switchON ? startSecondMovie() : 0;
}//startMovies Funtion END


void Events::startSecondMovie() {

 Shared_sfe::movie2->setScale(Shared_sf::window.getSize().x / (Shared_sf::window.getSize().x * 2.f),
						 Shared_sf::window.getSize().y / (Shared_sf::window.getSize().y * 2.f));
 Shared_sfe::movie2->fit(0, 0, Shared_Var::w, Shared_Var::h);
 Shared_sfe::movie2->setPosition(Shared_Var::w / 2, 0);

 if (Shared_Var::mov2SaveTime != 0) {
  Shared_sfe::movie2->play();
  Shared_bool::movie2Active = true;
 }
}

//
//Saves the basic settings; like, Volume and window size
//
inline void Save_to_Settings_ini(InitialSetup* initial) {
 if (Shared_Str::setting.is_open()) {
  if (Shared_bool::movie_is_Playing) {
   //Saves the 'first' volume to the saveable variables
   Shared_Save::volume1.setV((int)ceil(Shared_sfe::movie->getVolume()));

   if (Shared_Mod::oneMovie->switchON) {
	//Saves the 'Second' volume to the saveable variables
	Shared_Save::volume2.setV((int)ceil(Shared_sfe::movie2->getVolume()));
   }
   else{
	Shared_Save::volume2.setV(Shared_Save::volume2.getV(0));
   }
   print.Log_Info("Volume1: %s Volume2: %s", Shared_Save::volume1.getSave().c_str(),
						  Shared_Save::volume2.getSave().c_str());
  }
  else {
   //Saves the loaded volume instead of the actual volume, otherwise: access violiation...",
   Shared_Save::volume1.setV(Shared_Save::volume1.getV(0));
   Shared_Save::volume2.setV(Shared_Save::volume2.getV(0));
  
  }
  Shared_Save::window_Width.setV(Shared_sf::window.getSize().x);
  Shared_Save::window_Height.setV(Shared_sf::window.getSize().y);
  Shared_Save::One_Switch_On.setV(Shared_Mod::oneMovie->switchON);
  Shared_Save::maximized_On_Exit.setV(Shared_bool::maximized_On_Exit_Program);

  Save_Files::Variables_Settings_to_Save();
 }
}

void Events::SaveSettings() {
 string p = Shared_Str::current.string() + "/config\\Settings.ini";
 ofstream t;

 WINDOWPLACEMENT pl;
 GetWindowPlacement(Shared_sf::window.getSystemHandle(), &pl);
 switch (pl.flags) {
 case 0:
  Shared_bool::maximized_On_Exit_Program = false;
  break;
 case 2:
  Shared_bool::maximized_On_Exit_Program = true;
  break;
 }

 //Loads the Settings
 Shared_Str::setting.open(p, ios::out);
 Save_to_Settings_ini(initial);
 Shared_Str::setting.close();

 p = Shared_Str::movieSavePath;

 Shared_Str::movieFile.open(p, ios::out);
 //This should only save the movie when both movies is playing
 if (Shared_Str::movieFile.is_open() && Shared_bool::movie_is_Playing && Shared_Mod::oneMovie->switchON) {
  Shared_Save::mov1Time.setV(Shared_sfe::movie->getPlayingOffset().asSeconds());
  Shared_Save::mov1Path.setV(initial->ffs);
  Shared_Save::mov2Time.setV(Shared_sfe::movie2->getPlayingOffset().asSeconds());
  Shared_Save::mov2Offset.setV(Shared_sf::off.asSeconds());
  Shared_Save::mov2Path.setV(initial->mov);

  Save_Files::Variables_Movie_to_Save();
 }
 Shared_Str::movieFile.close();

 p = Shared_Str::current.string() + "\\config\\hash.vga";
 t.open(p);
 
 if (t.is_open()) {
  for (unsigned int a = 0; a < initial->allHash.size(); a++)
   t << initial->allHash[a] << endl;
 }
 t.close();
}