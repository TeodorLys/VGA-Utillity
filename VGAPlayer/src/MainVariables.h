#pragma once
#include "../src/Events/Events.h"
#include "InitialSetup.h"
#include "fanArt.h"
#include "../src/Events/Resized.h"
#include "../src/Events/keyPress.h"
#include "../src/Events/mouseEvent.h"
#include "../src/Events/movieDuration.h"
#include "../src/Events/MovieEvents.h"
#include "../src/MovieEvents/Single.h"
#include "../src/MovieEvents/Multi.h"
#include "Themes.h"
#include "../src/Events/Debugging.h"
#include "Audio.h"
#include "../src/Handlers/Context_Handler.h"
#include "../src/Handlers/Menu_Handler.h"
#include "Write_Field.h"
#include "../src/Shared/Shared_sfml_Objects.h"

bool windowClosed = false;
bool pause = true;
bool border;

int mousePosX = 0;
int mousePosY = 0;
int initx;  //Initial mouse position X
int inity;  //Initial mouse position Y
float mx;
float my;
bool beforeStart = false;
bool border_Infinity_Stopper = false;
bool moving_Second_Movie;
bool file_Open_All_Success = false;

struct objects {
 InitialSetup initial;
 Resized re;
 keyPress kp;
 mouseEvent me;
 Events ev;
 movieDuration md;
 movBase *movie;
 singleMovies singleMov;
 multiMovies multiMov;
 Debugging debug;
 Audio audio;
 Context_Handler context_Handle;
 Menu_Handler menu_Handle;

 objects::objects() : initial(&me, &audio, &context_Handle, &re),
  ev(&kp, &re, &initial, &me, &movie, &audio),
  kp(&ev, &movie, &debug),
  me(&ev,&audio),
  debug(Shared_sf::window, Shared_sf::mouse, Shared_sf::event, Shared_sf::sysFont),
  re(&initial), 
  md(&initial),
  audio(&initial), 
  context_Handle(&initial){}
};

