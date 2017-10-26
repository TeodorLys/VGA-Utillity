#pragma once
#include "Logger.h"

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
private:
 InitialSetup *initial;
public:
 Context_Handler(InitialSetup* initial_Object);
 void Menu_Activator(bool movie_Is_Playing, bool Mouse_Left_Click, bool Window_Is_Focused);
 void Show_Context_Menu(bool Mouse_Click, bool window_Is_Focused, ContextMenu &cM);

 void Show_Object_Selector(ContextMenu &cM, movBase &Movie_Object,
						   Debugging &debug, Write_Field &jump_field, float X, float Y, bool &Mouse_has_Clicked,
						   sfe::Movie &Movie_One, bool &Menu_is_Shown, Events &ev);

 void Menu_Object_Events(ContextMenu &cM, movBase &Movie_Object, Debugging &debug, Write_Field &jump_field,
						 float X, float Y, bool &Mouse_has_Clicked,
						 sfe::Movie &Movie_One, bool &Menu_is_Shown, Events &ev);
 void Menu_Object_Setup();
};

