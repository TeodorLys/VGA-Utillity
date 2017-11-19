//2017-05-01 19:26, Currently: 2384 lines of code
//2017-07-23 20:03, Currently: 3472 lines of code
//2017-08-02 20:36, Currently: 4123 lines of code
//2017-08-14 00:43, Currently: 5273 lines of code
#include <sfeMovie\Movie.hpp>
#include <boost\filesystem\operations.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <SFML\Window\Context.hpp>
#include "Main_Handler\Main_Render.h"
#include "Main_Handler\Main_Runtime_Check.h"
#include "Objects\Play_Pause_Icon.h"
#include "DEBUG_Defines.h"
#include "MainVariables.h"
#include "Events\Debugging.h"
#include "Objects\Switch.h"
#include "Objects\Buttons.h"
#include "Objects\ContextMenu.h"
#include "Events\Animation.h"
#include "Write_Field.h"
#include "Events\Actions.h"
#include "Save\Save_Files.h"

/*---(Shared Variables)---*/
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_String.h"
#include "Shared\Shared_Modules.h"
#include "Shared\Shared_sfml_Objects.h"
/*---(Shared Variables)---*/

#ifdef _ONLYSFMLs
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
Play_Pause_Icon *play;   //Makes it easier to call the constructor

void Main_Destructor() {
 delete play;
 if (Shared_bool::movie_is_Playing) {
  Shared_sfe::movie->stop();
  if (Shared_Mod::oneMovie->switchON) {
   Shared_sfe::movie2->stop();
   delete Shared_sfe::movie2;
  }
  delete Shared_sfe::movie;
 }
}

void Parse_Main_Arguments(char* c[]) {
 //I have no clue... sorry
 string movPath = boost::filesystem::system_complete(c[1]).string();
 
 Shared_sfe::movie = new sfe::Movie;  //Creates the movie object, because we do not call the initiation function when
									  //opening through a movie file

 if (!Shared_sfe::movie->openFromFile(movPath)) {
  int msg = MessageBox(NULL, L"Could not open the file format", L"Could not open File", MB_OKCANCEL);
  //Exits no matter what...
  if (msg == IDOK || IDCANCEL)
   exit(-1);
 }
 else {
  print.Log_Success("Successfully loaded %s", movPath);
  file_Open_All_Success = true;   //If the movie loading was successful.
 }
}


void Draw_End_Screen() {
 Shared_sf::window.clear(sf::Color(50, 50, 50));
 Shared_Mod::ret->draw();
 Shared_Mod::replay->draw();
 Shared_sf::window.display();
}


/////////////////////////////////////////////////////////////
/// \*This is a second thread* which means that the videos ///
/// \will play even though you move or resize the window  ///
/////////////////////////////////////////////////////////////
void Thread_Rendering(sf::RenderWindow *window) {
 window->setActive(false);
 Shared_sf::second_Window.setActive(false);
 while (window->isOpen()) {
  if (Shared_bool::movie_is_Playing && Main_Runtime_Check::border && !windowClosed) {
   obj.movie->updateMovies(*Shared_sfe::movie, *Shared_sfe::movie2);

   window->clear();   //Clears the RAM
   Shared_sf::second_Window.clear();

   if (Shared_bool::behind) {
	obj.movie->drawMovieInv(*Shared_sfe::movie, *Shared_sfe::movie2);
   }
   else {
	obj.movie->drawMovie(*Shared_sfe::movie, *Shared_sfe::movie2);
   }
   obj.movie->Draw_Text(Shared_sf::vol1, Shared_sf::vol2);
   obj.movie->Draw_Text(Shared_sf::tTimer, Shared_sf::smalltTimer);

   Shared_sf::second_Window.display();
   window->display();

  }	else {
   window->setActive(false);
   Shared_sf::second_Window.setActive(false);
   while (pause) {   //Pauses this thread, to release some CPU usage
	unique_lock<mutex> lk(m);
	cv.wait(lk);
	lk.unlock();
   }
   window->setActive(false);
   Shared_sf::second_Window.setActive(false);
  }
 }
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


//Desiding factor to what is being rendered
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

 //Menu
 if (!Shared_bool::movie_is_Playing && !Shared_bool::endOfMovie) {
  Shared_bool::menu_Is_Shown = true;
  Main_Render::Local_Menu_Render(obj.context_Handle, obj.debug);
 }
 //Movie play Locally
 else if (!border && !Shared_bool::endOfMovie) {
  Shared_bool::menu_Is_Shown = false;
  Main_Render::Local_Movie_Render(play, obj.movie, &obj.context_Handle, obj.debug);
  
  if (!beforeStart) {
   //Need to reset the window, otherwise coordinates gets weird.
   ShowWindow(Shared_sf::window.getSystemHandle(), SW_RESTORE);
   ShowWindow(Shared_sf::window.getSystemHandle(), SW_MAXIMIZE);
   beforeStart = true;
  }
 }
}/*--(Draw END)--*/


void Main_Window_PollEvent(std::thread &render) {
 while (Shared_sf::window.pollEvent(Shared_sf::event)) {
  switch (Shared_sf::event.type) {
  case sf::Event::Closed:
   printf("\n\n\n");
   obj.ev.SaveSettings();
   windowClosed = true;   //Variable for the second thread

   render.detach();   //Detaches the thread so it can safely exit		
   Shared_sf::window.close();   //Close the SFML window
   if (Shared_bool::second_Movie_Popout)
	Shared_sf::second_Window.close();
   FreeConsole();
   Main_Destructor();
   exit(0);
   break;

  case sf::Event::LostFocus:
   Shared_bool::focus = false;
   for (int Context_Index = 0; Context_Index < 2; Context_Index++) {
	obj.context_Handle.allCM[Context_Index].contextMenuShown = false;
	obj.context_Handle.allCM[Context_Index].showSelector();
   }
   break;

  case sf::Event::GainedFocus:
   Shared_bool::focus = true;
   break;

  //Checks and calls all of the mouse press functions in buttons and such...
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
   moving_Second_Movie = false;  //If the movie has been moved
   Shared_bool::doonce = false;
   Shared_bool::mouseClick = false;
   break;

  default:
   break;
  }

  //What keypressing to check like: play/pause, jump to write field or debugging write field 
  if (obj.debug.writing) {
   obj.debug.valueField();
  }
  else if (Write_Field::write().is_Writing) {
   Write_Field::write().value_Field(&Shared_sf::event);
  }
  else {
   obj.ev.checkKeypress(Shared_sf::event);
  }
 }//Poll event END
}


int main(int argc, char* argv[]) {
 print.Set_Level(Logger::LOG_INFO_LEVEL);

 //Debug, opens a specified movie on startup
 Shared_bool::set_Default_Movie = false;
 
 string t = argv[0];
 t.erase(t.find_last_of("\\"), t.length());
 Shared_Str::executing_Path =  t;

 if (argc > 1)   //the first value in argc is the executable path -- usually
  Parse_Main_Arguments(argv);

 //Initialize stuff
 obj.initial.initializeButtons();   //Creates new buttons and switches from the pointer variables
 Save_Files::Get_Saved_Files(&obj.audio, &obj.initial);   //Loads Settings and such


 if (Shared_bool::Start_Logging) {
  AllocConsole();
  FILE* new_stdout;
  freopen_s(&new_stdout, "CONOUT$", "w", stdout);
  print.setup();
  //AttachConsole(GetProcessId(GetStdHandle(-10)));
 }

 obj.initial.Setup_Window();   //Runs the initial movie parameters
 obj.initial.menuButtonsSettings();   //Initializes all of the menu buttons
 
 play = new Play_Pause_Icon;   //The variable must be global, but it cant be initialized until the windows has been initialized
 play->setSize(2.5);
 play->setColor(sf::Color(255, 255, 255, 0));

 thread render(bind(Thread_Rendering, &Shared_sf::window));   //Sets up the thread
 Shared_Mod::oneMovie->setBase();   //Basically a switch constructor, sets the size, color, etc...

 obj.initial.init_Debug(obj.debug);

 Main_Runtime_Check::Thread_Pause(&m, &pause);

 //Initilize through movie file, and it was successfull
 if (file_Open_All_Success) {
  Shared_Mod::oneMovie->switchON = false;
  Shared_bool::behind            = false;
  obj.movie						 = &obj.singleMov;

  obj.me.Initialize_Isolated_Movie(*Shared_sfe::movie, Shared_Var::hour, Shared_Var::minute, Shared_Var::second);
 }



 /*---(Runtime stuff)---*/
 while (Shared_sf::window.isOpen()) {
  !Shared_bool::movie_is_Playing ? obj.menu_Handle.Menu_Buttons(*Shared_sfe::movie, *Shared_sfe::movie2,
																obj.initial, obj.audio, obj.ev) : 0;

  Shared_bool::endOfMovie ? obj.menu_Handle.End_Screen(Shared_bool::doonce, *Shared_sfe::movie, obj.initial, *obj.movie) : 0;

  Shared_bool::endOfSecondMovie ? End_Of_Second_Movie_Load() : 0;   //If the second movie is over.
  tStart = chrono::high_resolution_clock::now();
  
  Main_Runtime_Check::Play_Pause_Active_Icon(play);  //Inlined function to check if the movie(s) status has changed

  //Checks if any context menu is open, and checks if any object is selected.
  for (size_t a = 0; a < 2; a++) {
   if (obj.context_Handle.allCM[a].contextMenuShown) {
	obj.context_Handle.Show_Object_Selector(obj.context_Handle.allCM[a], *obj.movie, obj.debug,
											Write_Field::write(), (float)Shared_sf::mouse.getPosition(Shared_sf::window).x,
											(float)Shared_sf::mouse.getPosition().y, Shared_bool::mouseClick,
											*Shared_sfe::movie, Shared_bool::menu_Is_Shown, obj.ev);
   }
  }

  //Changes the movie object, to multi or single. If it should ex. pause/play both movies or not
  if (!Shared_Mod::oneMovie->switchON && !Shared_bool::movie_is_Playing) {
   Shared_sf::theCrew.setFillColor(Animation::Lerp_Color(Shared_sf::theCrew.getFillColor(), sf::Color(0, 0, 0, 150), 19, "TheCrew"));
   obj.movie = &obj.singleMov;
  }
  else if(Shared_Mod::oneMovie->switchON && !Shared_bool::movie_is_Playing){
   Shared_sf::theCrew.setFillColor(Animation::Lerp_Color(Shared_sf::theCrew.getFillColor(), sf::Color(255, 255, 255, 255), 19, "TheCrew"));
   obj.movie = &obj.multiMov;
  }

  Main_Runtime_Check::When_Movie_is_Playing(obj.movie, obj.md, &cv, &m, &pause);
  
  Main_Window_PollEvent(render);

  //Second poll event, might be a mistake... but maybe not.
  if (Shared_bool::second_Movie_Popout) {
   Main_Runtime_Check::Popout_Window_PollEvent(obj.re);
  }

  //Hides the UI if the mouse is still, and is in fullscreen mode
  if (Shared_bool::isFullscreen) {
   obj.me.checkUI(tStart, tEnd, mousePosY, mousePosX, Shared_sf::mouse.getPosition().x, Shared_sf::mouse.getPosition().y);
  }
  else {
   //Resets all settings, just too be sure
   Shared_sf::window.setMouseCursorVisible(true);
   obj.me.set_Opacity_Info(255);
  }
  Draw();  //Just the drawing...
 }//Draw END
}//Main Function END