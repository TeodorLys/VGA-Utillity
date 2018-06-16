#pragma once
#include "Logger.h"
#include "Objects\ContextMenu.h"

class InitialSetup;
class ContextMenu;
class Actions;
class mouseEvent;
class Debugging;
class movBase;
class Write_Field;
class Events;

namespace sfe {
	class Movie;
};

class Context_Handler {
public:
 ContextMenu allCM[2];

#define mainMovie allCM[1]
#define basic allCM[0]

private:
 InitialSetup *initial;

 //These are just for ease of reading for functions
 ContextMenu *Priv_cM;
 movBase     *Priv_Movie_Object;
 Debugging   *Priv_debug;
 Write_Field *Priv_jump_field;
 sfe::Movie  *Priv_Movie_One;
 Events      *Priv_ev;
 


public:
 Context_Handler(InitialSetup* initial_Object);
 void Menu_Activator(bool movie_Is_Playing, bool Mouse_Left_Click, bool Window_Is_Focused);


 void Show_Object_Selector(ContextMenu &cM, movBase &Movie_Object,
						   Debugging &debug, Write_Field &jump_field, float X, float Y, bool &Mouse_has_Clicked,
						   sfe::Movie &Movie_One, bool &Menu_is_Shown, Events &ev);

 void Menu_Object_Setup();   //External "Constructor"... sort of

private:
 void Menu_Object_Events(float X, float Y, bool &Mouse_has_Clicked,bool &Menu_is_Shown);
 void Show_Context_Menu(bool Mouse_Click, bool window_Is_Focused, ContextMenu &cM);
};

