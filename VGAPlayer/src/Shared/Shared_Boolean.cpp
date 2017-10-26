#include "Shared_Boolean.h"

namespace Shared_bool {
 bool doonce                       = false;   //Infinity blocker
 bool mouseClick                   = false;
 bool movie_is_Playing             = false;   //If the movie is active
 bool isFullscreen                 = false;   //If the window is in BORDERLESS fullscreen 
 bool focus                        =  true;   //If the window has focus or not
 bool behind                       =  true;   //If the smaller movie should be hidden
 bool endOfMovie                   = false;
 bool menu_Is_Shown                =  true;
 bool movie2Active                 = false;
 bool endOfSecondMovie             = false;
 bool Maximized_on_Exit_Fullscreen = false;
 bool maximized_On_Exit_Program    = false;
 bool movie_Status_Changed		   = false;
 bool set_Default_Movie			   =  true;	
 bool second_Movie_Popout          = false;

 //Temporary!!, Debugger
 bool get = false;
};