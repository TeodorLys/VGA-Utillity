#include "Context_Handler.h"
#include "DEBUG_Defines.h"
#include "InitialSetup.h"
#include "Events\mouseEvent.h"
#include "Events\Debugging.h"
#include "Events\Events.h"
#include "Objects\ContextMenu.h"
#include "Objects\ContextMenuObjects.h"
#include "Menu_Handler.h"
#include "Write_Field.h"
#include "Events\Actions.h"
#include "Events\MovieEvents.h"

#include "Shared\Shared_Modules.h"
#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Boolean.h"
#include <sfeMovie\Movie.hpp>
#include <Windows.h>

using namespace std;

Context_Handler::Context_Handler(InitialSetup* initial_Object) : initial(initial_Object) {}

 void Context_Handler::Menu_Object_Setup(){
 basic.setup();
 basic.addObject(*Shared_Mod::about, "About", Shared_sf::sysFont);
 basic.addObject(*Shared_Mod::about, "DEBUG", Shared_sf::sysFont);
 basic.objectsSetup();
 print.Log_Info("Setup Basic Context Menu");

 mainMovie.setup();
 mainMovie.addObject(*Shared_Mod::mainMovText, "Play", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Pause", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Stop", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Jump to", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Fullscreen", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::spacers, 42);
 mainMovie.addObject(*Shared_Mod::mainMovText, "DEBUG", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::spacers, 42);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Return", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Replay", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::mainMovText, "About", Shared_sf::sysFont);
 mainMovie.addObject(*Shared_Mod::spacers, 42);
 mainMovie.addObject(*Shared_Mod::mainMovText, "Popout Second Movie", Shared_sf::sysFont);
 mainMovie.objectsSetup();
 print.Log_Info("Setup 'During movie' Context Menu");
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// \Handles all of the context menu clicks and
/// \When certain menus should be shown																			 
////////////////////////////////////////////////////////////////////////////////////////////////
void Context_Handler::Menu_Activator(bool movie_Is_Playing, bool Mouse_Left_Click, bool Window_Is_Focused) {
 if (movie_Is_Playing) {
  basic.contextMenuShown = false;
  Show_Context_Menu(Mouse_Left_Click, Window_Is_Focused, mainMovie);
 } else {
  mainMovie.contextMenuShown = false;
  Show_Context_Menu(Mouse_Left_Click, Window_Is_Focused, basic);
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


void Context_Handler::Show_Object_Selector(ContextMenu &cM, movBase &Movie_Object, Debugging &debug, 
										   Write_Field &jump_field, float X, float Y, bool &Mouse_has_Clicked,
										   sfe::Movie &Movie_One, bool &Menu_is_Shown, Events &ev) {
 Priv_cM = &cM;
 Priv_Movie_Object = &Movie_Object;
 Priv_debug = &debug;
 Priv_jump_field = &jump_field;
 Priv_Movie_One = &Movie_One;
 Priv_ev = &ev;
 cM.showSelector() ? Menu_Object_Events(X, Y, Mouse_has_Clicked, Menu_is_Shown) : 0;
}

void Context_Handler::Menu_Object_Events(float X, float Y, bool &Mouse_has_Clicked, bool &Menu_is_Shown) {
  if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("About")].textRect) && Actions::Click() && !Mouse_has_Clicked) {
   int msg = MessageBox(NULL, L"VGA-Player ALPHA v1.1\nmade by Teodor", L"About VGA-Player", MB_OK);
   Mouse_has_Clicked = true;
  } else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Return")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Menu_Handler::Return_To_Menu(*Priv_Movie_Object);
   Mouse_has_Clicked = true;
  } else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Replay")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Menu_Handler::Replay_Movies(*Priv_Movie_One, *Priv_Movie_Object);
   Mouse_has_Clicked = true;
  } else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("DEBUG")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Priv_debug->setPosition(sf::Vector2f(X, Y));
   Priv_debug->writing = true;
   Mouse_has_Clicked = true;
  }
  else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Jump to")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Priv_jump_field->setPosition(X, Y);
   Priv_jump_field->is_Writing = true;
   Mouse_has_Clicked = true;
  }
  else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Play")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Priv_Movie_Object->play();
  }
  else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Pause")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Priv_Movie_Object->pause();
  }
  else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Stop")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Priv_Movie_Object->stop();
   Priv_Movie_Object->play();
  }
  else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Fullscreen")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   if (Shared_bool::isFullscreen)
	Priv_ev->exitFullscreen(Shared_sf::window);
   else
	Priv_ev->enterFullscreen(Shared_sf::window);
  }
  else if (Actions::Hover(Priv_cM->objects[Priv_cM->GetIndex("Popout Second Movie")].textRect) && Actions::DownClick() && !Mouse_has_Clicked) {
   Priv_ev->Popout_Second_Window();
  }
 }