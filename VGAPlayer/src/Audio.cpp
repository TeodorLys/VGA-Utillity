#include <sfeMovie\Movie.hpp>
#include "Audio.h"
#include "../src/Events/Actions.h"
#include "../src/Events/mouseEvent.h"
#include "InitialSetup.h"
#include "../src/Objects/Switch.h"
#include "../src/Shared/Shared_sfml_Objects.h"
#include "../src/Shared/Shared_sfe_Movie.h"
#include "../src/Shared/Shared_Modules.h"

using namespace std;

inline void volume_Visual_Set(int &vol, const int offset) {
 Shared_sfe::movie->setVolume((float)vol);
 Shared_sf::vol1.setString(to_string(vol));
}
inline void volume_Visual_Set(float &vol2, const int offset) {
 Shared_sfe::movie2->setVolume(vol2);
 Shared_sf::vol2.setString(to_string((int)vol2));
}

Audio::Audio(InitialSetup *initial_Object) : initial(initial_Object){}

void Audio::set_Volume_at_Runtime() {
 if (!Shared_Mod::oneMovie->switchON)
  goto Single;

 if (Actions::Movie_Two_Hover(Shared_sf::mouse, Shared_sf::window, *Shared_sfe::movie2)) {

  if (Actions::Mouse_Wheel_Moved() && second_Mov_Vol != 100) {
   second_Mov_Vol += Audio_Off;
   volume_Visual_Set(second_Mov_Vol, Audio_Off);
  } else if (!Actions::Mouse_Wheel_Moved() && second_Mov_Vol != 0) {
   second_Mov_Vol -= Audio_Off;
   volume_Visual_Set(second_Mov_Vol, Audio_Off);
  }
 } 
 else {

 Single:
  if (Actions::Mouse_Wheel_Moved() && first_Mov_Vol != 100) {
   first_Mov_Vol += Audio_Off;
   volume_Visual_Set(first_Mov_Vol, Audio_Off);
  } else if (!Actions::Mouse_Wheel_Moved() && first_Mov_Vol != 0) {
   first_Mov_Vol -= Audio_Off;
   volume_Visual_Set(first_Mov_Vol, Audio_Off);
  }
 }

}

void Audio::Initialize_First_Movie_Timer(sfe::Movie &Movie_One , size_t &Hour, size_t &Minute, size_t &Second) {
 float buff = Movie_One.getDuration().asSeconds() / 60;
 Hour = (int)buff / 60;
 Minute = (int)buff - (Hour * 60);
 Second = (int)Movie_One.getDuration().asSeconds() - (((Hour * 60) * 60) + (Minute * 60));

}

void Audio::Initialize_Second_Movie_Timer(sfe::Movie &Movie_Two, size_t &Small_Hour, size_t &Small_Minute, size_t &Small_Second) {
 float buff = Movie_Two.getDuration().asSeconds() / 60;
 Small_Hour = (int)buff / 60;
 Small_Minute = (int)buff - (Small_Hour * 60);
 Small_Second = (int)Movie_Two.getDuration().asSeconds() - (((Small_Hour * 60) * 60) + (Small_Minute * 60));
}
