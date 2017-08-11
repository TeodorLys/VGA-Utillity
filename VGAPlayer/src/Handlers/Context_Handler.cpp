#include "Context_Handler.h"
#include "DEBUG_Defines.h"
#include "InitialSetup.h"
#include "Events\mouseEvent.h"
#include "Events\Debugging.h"
#include "Objects\ContextMenu.h"
#include "Menu_Handler.h"
#include "Write_Field.h"
#include "Shared\Shared_Modules.h"
#include "Shared\Shared_sfml_Objects.h"
#include <Windows.h>

using namespace std;

Context_Handler::Context_Handler(InitialSetup* initial_Object) : initial(initial_Object) {}


 void Context_Handler::Menu_Object_Setup(){
 Shared_Mod::basic.setup();

 Shared_Mod::basic.addObject(*Shared_Mod::about, "About", Shared_sf::sysFont);
 Shared_Mod::basic.addObject(*Shared_Mod::about, "DEBUG", Shared_sf::sysFont);
 Shared_Mod::basic.objectsSetup();
 Logger::log().Log_Info("Setup Basic Context Menu");

 Shared_Mod::mainMovie.setup();
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "Play", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "Pause", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "Stop", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "Jump to", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::spacers, 42);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "DEBUG", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::spacers, 42);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "Return", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "Replay", Shared_sf::sysFont);
 Shared_Mod::mainMovie.addObject(*Shared_Mod::mainMovText, "About", Shared_sf::sysFont);
 Shared_Mod::mainMovie.objectsSetup();
 Logger::log().Log_Info("Setup 'During playing movie' Context Menu");
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// \Handles all of the context menu clicks and
/// \When certain menus should be shown																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void Context_Handler::Menu_Activator(bool movie_Is_Playing, bool Mouse_Left_Click, bool Window_Is_Focused) {
 if (movie_Is_Playing) {
  Shared_Mod::basic.contextMenuShown = false;
  Show_Context_Menu(Mouse_Left_Click, Window_Is_Focused, Shared_Mod::mainMovie);
 } else {
  Shared_Mod::mainMovie.contextMenuShown = false;
  Show_Context_Menu(Mouse_Left_Click, Window_Is_Focused, Shared_Mod::basic);
 }
}


void Context_Handler::Show_Context_Menu(bool Mouse_Click, bool window_Is_Focused, ContextMenu &cM) {
 if (Mouse_Click && window_Is_Focused) {
  cM.setPosition(Shared_sf::window, Shared_sf::mouse);
  cM.contextMenuShown = true;
 } else if (!cM.isOver()) {
  cM.contextMenuShown = false;
 }
}


void Context_Handler::Show_Object_Selector(ContextMenu &cM, movBase &Movie_Object, 
										   Debugging &debug, Write_Field &jump_field, float X, float Y, bool &Mouse_has_Clicked,
										   sfe::Movie &Movie_One, bool &Menu_is_Shown) {
 cM.showSelector() ? Menu_Object_Events(cM, Movie_Object, debug, jump_field, X, Y, Mouse_has_Clicked, Movie_One, Menu_is_Shown) : 0;
}

void Context_Handler::Menu_Object_Events(ContextMenu &cM, movBase &Movie_Object, Debugging &debug, Write_Field &jump_field,float X,
										 float Y, bool &Mouse_has_Clicked,
										 sfe::Movie &Movie_One, bool &Menu_is_Shown) {
  if (Actions::Hover(cM.objects[cM.GetIndex("About")].textRect) && Actions::Click() && !Mouse_has_Clicked) {
   int msg = MessageBox(NULL, L"VGA Player ALPHA v0.1\nmade by Teodor", L"About VGA Player", MB_OK);
   Mouse_has_Clicked = true;
  } else if (Actions::Hover(cM.objects[cM.GetIndex("Return")].textRect) && Actions::Click() && !Mouse_has_Clicked) {
   Menu_Handler::Return_To_Menu(Movie_Object);
   Mouse_has_Clicked = true;
  } else if (Actions::Hover(cM.objects[cM.GetIndex("Replay")].textRect) && Actions::Click() && !Mouse_has_Clicked) {
   Menu_Handler::Replay_Movies(Movie_One, Movie_Object);
   Mouse_has_Clicked = true;
  } else if (Actions::Hover(cM.objects[cM.GetIndex("DEBUG")].textRect) && Actions::Click() && !Mouse_has_Clicked) {
   debug.setPosition(sf::Vector2f(X, Y));
   debug.writing = true;
   Mouse_has_Clicked = true;
  }
  else if (Actions::Hover(cM.objects[cM.GetIndex("Jump to")].textRect) && Actions::Click() && !Mouse_has_Clicked) {
   jump_field.setPosition(X, Y);
   jump_field.is_Writing = true;
   Mouse_has_Clicked = true;
  }
 }