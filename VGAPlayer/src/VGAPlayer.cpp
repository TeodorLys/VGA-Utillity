//2017-05-01 19:26, Currently: 2384 lines of code
//2017-07-23 20:03, Currently: 3472 lines of code
//2017-08-02 20:36, Currently: 4123 lines of code
#include <sfeMovie\Movie.hpp>
#include <boost\filesystem\operations.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <SFML\Window\Context.hpp>
#include "../src/Objects/Play_Pause_Icon.h"
#include "DEBUG_Defines.h"
#include "MainVariables.h"
#include "../src/Events/Debugging.h"
#include "../src/Objects/Switch.h"
#include "../src/Objects/Buttons.h"
#include "../src/Objects/ContextMenu.h"
#include "../src/Events/Animation.h"
#include "Write_Field.h"
#include "../src/Save/Save_Files.h"
#include "../src/Shared/Shared_Boolean.h"
#include "../src/Shared/Shared_sfe_Movie.h"
#include "../src/Shared/Shared_Variables.h"
#include "../src/Shared/Shared_String.h"
#include "../src/Shared/Shared_Modules.h"
#include "../src/Shared/Shared_sfml_Objects.h"

#ifdef _ONLYSFML
#include "stdafx.h"
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

using namespace std;

std::condition_variable cv;   //Thread lock
std::mutex m;

chrono::high_resolution_clock::time_point tStart;
chrono::high_resolution_clock::time_point tEnd;
objects obj;
Play_Pause_Icon *play;
bool yes = false;
int it = 0;

void Parse_Main_Arguments(char* c[]) {
 string movPath = boost::filesystem::system_complete(c[1]).string();
 Shared_sfe::movie = new sfe::Movie;

 if (!Shared_sfe::movie->openFromFile(movPath)) {
  int msg = MessageBox(NULL, L"Could not open the file format", L"Could not open File", MB_OKCANCEL);
  if (msg == IDOK || IDCANCEL) {
   exit(-1);
  }
 }
 else {
  Logger::log().Log_Success("Successfully loaded %s", movPath);
  file_Open_All_Success = true;
 }
}


void Draw_End_Screen() {
 Shared_sf::window.clear(sf::Color(50, 50, 50));
 Shared_Mod::ret->draw();
 Shared_Mod::replay->draw();
 Shared_sf::window.display();
}


/////////////////////////////////////////////////////////////
/// \Renders the menu objects							  ///
/////////////////////////////////////////////////////////////
void Local_Menu_Render() {
	Shared_sf::window.clear();   //Clears the RAM of all unused stuff /*I think*/
	
	Shared_sf::window.draw(Shared_sf::b);   //Draws the background
	Shared_sf::window.draw(Shared_sf::theCrew);
	Shared_Mod::play->draw();   //Draws the play button 
	Shared_Mod::ffstv->draw();   //Draws the OPEN FFSTV VIDEO button
	Shared_Mod::film->draw();   //Draws the OPEN MOVIE FILE button

	Shared_Mod::oneMovie->draw();

	Shared_Mod::basic.contextMenuShown ? Shared_Mod::basic.draw(Shared_sf::window) : 0;

	obj.debug.writing ? obj.debug.draw() : 0;

	Shared_sf::window.display();   //Display what was just drawn
}


/////////////////////////////////////////////////////////////
/// \Renders the movie(s) Locally                         ///
/////////////////////////////////////////////////////////////
void Local_Movie_Render() {
 obj.movie->updateMovies(Shared_sf::window,
						 *Shared_sfe::movie, *Shared_sfe::movie2);
 Shared_sf::window.clear();
 
 if (Shared_bool::behind) {
  obj.movie->drawMovieInv(obj.initial, Shared_sf::window,
						  *Shared_sfe::movie, *Shared_sfe::movie2);
 }
 else {
  obj.movie->drawMovie(obj.initial, Shared_sf::window,
					   *Shared_sfe::movie, *Shared_sfe::movie2);
 }

 obj.movie->Draw_Text(Shared_sf::window,
					  Shared_sf::vol1, Shared_sf::vol2);
 obj.movie->Draw_Text(Shared_sf::window,
					  Shared_sf::tTimer, Shared_sf::smalltTimer);

 play->Draw();

 if (Shared_Mod::mainMovie.contextMenuShown) {
  Shared_Mod::mainMovie.draw(Shared_sf::window);
 }

 if (obj.debug.writing) {
  obj.debug.draw();
 }
 else if (Write_Field::write().is_Writing) {
  Write_Field::write().setOpacity(255);
 }

 if (!Write_Field::write().Is_Invisible()) {
  if (!Write_Field::write().is_Writing)
   Write_Field::write().setOpacity(Animation::Lerp_Opacity(Write_Field::write().getColor().a, 10));
  Write_Field::write().Draw();
 }
 Shared_sf::window.display();
}


/////////////////////////////////////////////////////////////
/// \This is a second thread, which means that the videos ///
/// \will play even though you move or resize the window  ///
/////////////////////////////////////////////////////////////
void Thread_Rendering(sf::RenderWindow *window) {
 window->setActive(false);
 while (window->isOpen()) {
  if (Shared_bool::movie_is_Playing && border && !windowClosed) {
   obj.movie->updateMovies(*window, *Shared_sfe::movie, *Shared_sfe::movie2);

   window->clear();   //Clears the RAM
   if (Shared_bool::behind) {
	obj.movie->drawMovieInv(obj.initial, Shared_sf::window,
							*Shared_sfe::movie, *Shared_sfe::movie2);
   }
   else {
	obj.movie->drawMovie(obj.initial, Shared_sf::window,
						 *Shared_sfe::movie, *Shared_sfe::movie2);
   }
   obj.movie->Draw_Text(*window, Shared_sf::vol1, Shared_sf::vol2);
   obj.movie->Draw_Text(*window, Shared_sf::tTimer, Shared_sf::smalltTimer);

   window->display();
  }	else {
   window->setActive(false);
   while (pause) {
	unique_lock<mutex> lk(m);
	cv.wait(lk);
	lk.unlock();
   }
   window->setActive(false);
  }
 }
}


void Thread_Start() {
 lock_guard<mutex> lk(m);
 pause = false;
 cv.notify_one();
}
void Thread_Pause() {
 lock_guard<mutex> lk(m);
 pause = true;
}


void End_Of_Second_Movie_Load() {
 if (Shared_Mod::secondReplay->Hover(sf::Color(175, 175, 175), 2)) {
  if (Actions::Click() && !Shared_bool::doonce && !Shared_bool::mouseClick && Shared_bool::focus) {
   Shared_sfe::movie2->stop();
   if (obj.initial.LoadMovie(2, &Shared_sfe::movie2)) {
	obj.ev.startSecondMovie();
	Shared_bool::endOfSecondMovie = false;
   }
   Shared_bool::doonce = true;
  }
 }
}


void Draw() {
 if (!Shared_bool::menu_Is_Shown && Shared_sfe::movie->getPlayingOffset().asSeconds() >= Shared_sfe::movie->getDuration().asSeconds()) {
  Shared_bool::endOfMovie = true;
  Shared_bool::movie_is_Playing = false;
  Shared_bool::movie2Active = false;
  Draw_End_Screen();
 }
 else if (Shared_Mod::oneMovie->switchON) {
  if (!Shared_bool::menu_Is_Shown && Shared_sfe::movie2->getPlayingOffset().asSeconds() >= Shared_sfe::movie2->getDuration().asSeconds())
   Shared_bool::endOfSecondMovie = true;
 }

 ///Menu
 if (!Shared_bool::movie_is_Playing && !Shared_bool::endOfMovie) {
  Shared_bool::menu_Is_Shown = true;
  Local_Menu_Render();
 }
 ///Movie play Locally
 else if (!border && !Shared_bool::endOfMovie) {
  Shared_bool::menu_Is_Shown = false;
  Local_Movie_Render();
  
  if (!beforeStart) {
   //Need to reset the window, otherwise coordinates are weird.
   ShowWindow(Shared_sf::window.getSystemHandle(), SW_RESTORE);
   ShowWindow(Shared_sf::window.getSystemHandle(), SW_MAXIMIZE);
   beforeStart = true;
  }
 }
}


int main(int argc, char* argv[]) {
 Logger::log().Set_Level(Logger::LOG_INFO_LEVEL);

 string t = argv[0];
 t.erase(t.find_last_of("\\"), t.length());
 Shared_Str::executing_Path = t;

 if (argc > 1)
  Parse_Main_Arguments(argv);

 //Initialize stuff
 obj.initial.initializeButtons();
 Save_Files::Get_Saved_Files(&obj.audio, &obj.initial);   //settings.txt
 obj.initial.Setup_Window();   //Runs the initial movie parameters
 obj.initial.menuButtonsSettings();   //Initializes all of the menu buttons
 
 play = new Play_Pause_Icon;
 play->setSize(2.5);
 play->setColor(sf::Color(255, 255, 255, 0));
 thread render(bind(Thread_Rendering, &Shared_sf::window));   //Sets up the thread
 Shared_Mod::oneMovie->setBase();

 obj.initial.init_Debug(obj.debug);

 Thread_Pause();

 //Initilize through file, and it was successfull
 if (file_Open_All_Success) {
  Shared_Mod::oneMovie->switchON = false;
  Shared_bool::behind = false;
  obj.movie = &obj.singleMov;

  obj.me.Initialize_Isolated_Movie(*Shared_sfe::movie, Shared_Var::hour, Shared_Var::minute, Shared_Var::second);
  
  obj.movie->t();
 }

 /*---(Runtime stuff)---*/
 while (Shared_sf::window.isOpen()) {
  !Shared_bool::movie_is_Playing ? obj.menu_Handle.Menu_Buttons(*Shared_sfe::movie, *Shared_sfe::movie2,
																obj.initial, obj.audio, obj.ev) : 0;

  Shared_bool::endOfMovie ? obj.menu_Handle.End_Screen(Shared_bool::doonce, *Shared_sfe::movie, obj.initial, *obj.movie) : 0;

  Shared_bool::endOfSecondMovie ? End_Of_Second_Movie_Load() : 0;
  tStart = chrono::high_resolution_clock::now();
  
  if (Shared_bool::movie_Status_Changed) {
   if (Shared_sfe::movie->getStatus() == sfe::Status::Paused) {
	play->set_Paused(true);
   }
   else {
	play->set_Paused(false);
   }
   play->setSize(Animation::Lerp_float(play->getSize(), 3, 0.025f));
   play->setColor(sf::Color(255, 255, 255, Animation::Lerp_Cosine(play->getColor().a, 50, 4, it, yes)));
   if (yes) {
	Shared_bool::get = false;
	Shared_bool::movie_Status_Changed = false;
   }
  }
  else if (yes) {
   it = 0;
   play->setSize(2.5);
   play->setColor(sf::Color(255, 255, 255, 0));
   yes = false;
  }

  //Context stuff
  for (size_t a = 0; a < 2; a++) {
   if (Shared_Mod::allCM[a].contextMenuShown) {
	obj.context_Handle.Show_Object_Selector(Shared_Mod::allCM[a], *obj.movie, obj.debug,
											Write_Field::write(), (float)Shared_sf::mouse.getPosition(Shared_sf::window).x,
											(float)Shared_sf::mouse.getPosition().y, Shared_bool::mouseClick,
											*Shared_sfe::movie, Shared_bool::menu_Is_Shown);
   }
  }

  if (!Shared_Mod::oneMovie->switchON && !Shared_bool::movie_is_Playing) {
   Shared_sf::theCrew.setFillColor(Animation::Lerp_Color(Shared_sf::theCrew.getFillColor(), sf::Color(0, 0, 0, 150), 19, "TheCrew"));
   obj.movie = &obj.singleMov;
  }
  else if(Shared_Mod::oneMovie->switchON && !Shared_bool::movie_is_Playing){
   Shared_sf::theCrew.setFillColor(Animation::Lerp_Color(Shared_sf::theCrew.getFillColor(), sf::Color(255, 255, 255, 255), 19, "TheCrew"));
   obj.movie = &obj.multiMov;
  }

  if (Shared_bool::movie_is_Playing) {
   if (Shared_Mod::oneMovie->switchON) {
	if (Actions::Movie_Two_Hover(Shared_sf::mouse, Shared_sf::window, *Shared_sfe::movie2) && Actions::DownClick() && !moving_Second_Movie && !Shared_bool::mouseClick) {
	  //Save the mouse locations, once -- when second movie is clicked
	  initx = Shared_sf::mouse.getPosition(Shared_sf::window).x;
	  inity = Shared_sf::mouse.getPosition(Shared_sf::window).y;
	  mx = Shared_sfe::movie2->getPosition().x;
	  my = Shared_sfe::movie2->getPosition().y;

	  moving_Second_Movie = true;
	}
	if (moving_Second_Movie) {
	 Shared_sfe::movie2->setPosition(sf::Vector2f(Shared_sf::mouse.getPosition(Shared_sf::window).x + (mx - initx),
									 Shared_sf::mouse.getPosition(Shared_sf::window).y + (my - inity)));
	}
   }

   if (Shared_sf::mouse.getPosition(Shared_sf::window).x >= 0 && Shared_sf::mouse.getPosition(Shared_sf::window).y <= 0) {
	if (Actions::DownClick() && !border_Infinity_Stopper && !Shared_bool::mouseClick) {
	 Shared_sf::window.setActive(false);
	 Thread_Start();

	 border = true;
	 border_Infinity_Stopper = true;
	}
   }
   else {
	if (border_Infinity_Stopper) {
	 //Pauses the thread, so the CPU dont get angry at me
	 Shared_sf::window.setActive(false);

	 Thread_Pause();

	 border = false;
	 border_Infinity_Stopper = false;
	}
   }
   obj.movie->movieTimers(obj.md);
  }
  else if (!Shared_bool::movie_is_Playing && beforeStart) {
   beforeStart = false;
  }

  while (Shared_sf::window.pollEvent(Shared_sf::event)) {
   switch (Shared_sf::event.type) {
   case sf::Event::Closed:
	printf("\n\n\n");
	obj.ev.SaveSettings();
	windowClosed = true;   //Variable for the second thread

	Sleep(100);

	render.detach();   //Detaches the thread so it can safely exit		
	Shared_sf::window.close();   //Close the SFML window
	break;

   case sf::Event::LostFocus:
	Shared_bool::focus = false;
	for (int Context_Index = 0; Context_Index < 2; Context_Index++) {
	 Shared_Mod::allCM[Context_Index].contextMenuShown = false;
	 Shared_Mod::allCM[Context_Index].showSelector();
	}
	break;

   case sf::Event::GainedFocus:
	Shared_bool::focus = true;
	break;

   case sf::Event::MouseButtonPressed:
	if (Shared_sf::mouse.isButtonPressed(sf::Mouse::Middle)) {
	 Shared_bool::movie_Status_Changed = true;
	 if (obj.movie->is_any_Movie_Paused())
	  obj.movie->play();
	 else
	  obj.movie->pause();
	}
	obj.context_Handle.Menu_Activator(Shared_bool::movie_is_Playing,
									  Shared_sf::mouse.isButtonPressed(sf::Mouse::Right), Shared_bool::focus);
	Shared_Mod::oneMovie->clickSwitch();
	Shared_bool::mouseClick = true;
	obj.debug.writing = false;
	Write_Field::write().is_Writing = false;
	break;

   case sf::Event::MouseButtonReleased:
	//If the movie has been moved
	moving_Second_Movie ? moving_Second_Movie = false : 0;

	Shared_bool::doonce = false;
	Shared_bool::mouseClick = false;
	break;

   default:
	break;
   }

   if (obj.debug.writing) {
	obj.debug.valueField();
   }
   else if (Write_Field::write().is_Writing) {
	Write_Field::write().value_Field(&Shared_sf::event);
   }
   else {
	//print.Log_Info("Key: %i", static_cast<int>(Shared_sf::event.text.unicode));
	obj.ev.checkKeypress(Shared_sf::event);
   }

  }//Poll event END

  if (Shared_bool::isFullscreen) {
   obj.me.checkUI(tStart, tEnd, mousePosY, mousePosX, Shared_sf::mouse.getPosition().x, Shared_sf::mouse.getPosition().y);
  }
  else {
   Shared_sf::window.setMouseCursorVisible(true);
   obj.me.set_Opacity_Info(255);
  }
  Draw();
 }//Draw END
}//Main Function END