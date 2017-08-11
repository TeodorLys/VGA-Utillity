#include <sfeMovie\Movie.hpp>
#include "movieDuration.h"
#include "InitialSetup.h"
#include "Objects\Switch.h"
#include "Objects\Buttons.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_String.h"
#include "Shared\Shared_Modules.h"

using namespace std;

movieDuration::movieDuration(InitialSetup* initial_Object) : initial(initial_Object){}

void movieDuration::Timer() {

 if (Shared_bool::movie_is_Playing) {
  currentHour = ((unsigned int)Shared_sfe::movie->getPlayingOffset().asSeconds() / 60) / 60;
  currentMinute = (unsigned int)Shared_sfe::movie->getPlayingOffset().asSeconds() / 60 - (currentHour * 60);
  currentSecond = ((unsigned int)Shared_sfe::movie->getPlayingOffset().asSeconds() - (currentMinute * 60)) - ((currentHour * 60) * 60);

  Shared_Str::strTime = to_string(currentHour) + ":" + to_string(currentMinute) + ":" + to_string(currentSecond) + "  /  " +
   to_string(Shared_Var::hour) + ":" + to_string(Shared_Var::minute) + ":" + to_string(Shared_Var::second);

  Shared_sf::tTimer.setString(Shared_Str::strTime);
 }
}

void movieDuration::smallTimer() {
 if (Shared_bool::movie_is_Playing) {
  if (Shared_Mod::oneMovie->switchON) {
   smallcurrentHour = ((unsigned int)Shared_sfe::movie2->getPlayingOffset().asSeconds() / 60) / 60;
   smallcurrentMinute = (unsigned int)Shared_sfe::movie2->getPlayingOffset().asSeconds() / 60 - (smallcurrentHour * 60);
   smallcurrentSecond = ((unsigned int)Shared_sfe::movie2->getPlayingOffset().asSeconds() - (smallcurrentMinute * 60)) - ((smallcurrentHour * 60) * 60);

   Shared_Str::smallstrTime = to_string(smallcurrentHour) + ":" + to_string(smallcurrentMinute) + ":" + to_string(smallcurrentSecond) + "  /  " +
	to_string(Shared_Var::smallhour) + ":" + to_string(Shared_Var::smallminute) + ":" + to_string(Shared_Var::smallsecond);

   Shared_sf::smalltTimer.setString(Shared_Str::smallstrTime);

  }
 }
}