#include <sfeMovie\Movie.hpp>
#include <mutex>
#include <condition_variable>
#include <SFML\Window\Event.hpp>
#include "Main_Runtime_Check.h"
#include "Events\Actions.h"
#include "Objects\Switch.h"
#include "Events\MovieEvents.h"
#include "Events\movieDuration.h"
#include "Events\Animation.h"
#include "Objects\Play_Pause_Icon.h"
#include "Events\Resized.h"


#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_Modules.h"

/*-(Initializes the static variables)-*/
int Main_Runtime_Check::initx = 0;
int Main_Runtime_Check::inity = 0;
int Main_Runtime_Check::mx = 0;
int Main_Runtime_Check::my = 0;
bool Main_Runtime_Check::border = false;
bool Main_Runtime_Check::border_Infinity_Stopper = false;
bool Main_Runtime_Check::beforeStart = false;
bool Main_Runtime_Check::moving_Second_Movie = false;



void Thread_Start(std::condition_variable *cv, std::mutex *m, bool *pause) {
 print.Log_Warning("Started the Thread...!");
 std::lock_guard<std::mutex> lk(*m);
 *pause = false;
 cv->notify_one();
}

void Main_Runtime_Check::Thread_Pause(std::mutex *m, bool *pause) {
 print.Log_Warning("Paused the Thread...!");
 std::lock_guard<std::mutex> lk(*m);
 *pause = true;
}


//Runtime/Constant Checking, if something has changed or has been clicked
void Main_Runtime_Check::When_Movie_is_Playing(movBase *movie, movieDuration &md, std::condition_variable *cv, std::mutex *m, bool *pause, bool *moving_Second_window) {
	if (Shared_bool::movie_is_Playing) {
		if (Shared_Mod::oneMovie->switchON && !Shared_bool::second_Movie_Popout) {
			if (Actions::Movie_Two_Hover(Shared_sf::mouse, Shared_sf::window, *Shared_sfe::movie2) && Actions::DownClick() && !moving_Second_Movie && !Shared_bool::mouseClick) {
				//As an offset for the mouse position relative to the second movie window
				initx = Shared_sf::mouse.getPosition(Shared_sf::window).x;
				inity = Shared_sf::mouse.getPosition(Shared_sf::window).y;
				mx = static_cast<int>(Shared_sfe::movie2->getPosition().x);
				my = static_cast<int>(Shared_sfe::movie2->getPosition().y);

				*moving_Second_window = true;  //Says to other statements that the user is moving the second window
			}
			if (*moving_Second_window) {
				Shared_sfe::movie2->setPosition(sf::Vector2f((float)Shared_sf::mouse.getPosition(Shared_sf::window).x + (mx - initx),
					(float)Shared_sf::mouse.getPosition(Shared_sf::window).y + (my - inity)));
			}
		}

		if (Shared_sf::mouse.getPosition(Shared_sf::window).x >= 0 && Shared_sf::mouse.getPosition(Shared_sf::window).y <= 0
			|| Shared_sf::mouse.getPosition(Shared_sf::second_Window).x >= 0 &&
			Shared_sf::mouse.getPosition(Shared_sf::second_Window).y <= 0 && Shared_bool::second_Movie_Popout) {

			if (Actions::DownClick() && !border_Infinity_Stopper && !Shared_bool::mouseClick) {
				//Pauses the thread, so the CPU dont get angry at me
				Shared_sf::window.setActive(false);
				if (Shared_bool::second_Movie_Popout)
					Shared_sf::second_Window.setActive(false);

				Thread_Start(cv, m, pause);

				border = true;   //If the mouse IS over the window border
				border_Infinity_Stopper = true;   //So it only starts the thread once.
			}
		}
		else {
			if (border_Infinity_Stopper) {
				Shared_sf::window.setActive(false);
				if (Shared_bool::second_Movie_Popout)
					Shared_sf::second_Window.setActive(false);

				Thread_Pause(m, pause);
				border = false;   //If the mouse ISNT over the window border
				border_Infinity_Stopper = false;   //So it only pauses the thread once.
			}
		}
		movie->movieTimers(md);  //Update the movie timers
	}
	else if (!Shared_bool::movie_is_Playing && beforeStart) {
		beforeStart = false;
	}
}/*--(When_Movie_Is_Playing END)--*/


 //Displays the play/pause icon, when changing the movie's state
void Main_Runtime_Check::Play_Pause_Active_Icon(Play_Pause_Icon *play) {

 static bool yes;  //An external checker. Used to: return true when the animation is done.
 static int incremental_Lerp;  //Gives me access to the progression of the animation 

 if (Shared_bool::movie_Status_Changed) {
  play->set_Paused(Shared_sfe::movie->getStatus() == sfe::Status::Paused);  //Gives the play icon access to the movie status
  play->setSize(Animation::Lerp_float(play->getSize(), 3, 0.025f));  //Animates the play size
  play->setColor(sf::Color(255, 255, 255, Animation::Lerp_Cosine(play->getColor().a, 50, 4, incremental_Lerp, yes)));  //Animates the opacity
  if (yes) {
   Shared_bool::get = false;   //Just for the debugger window.
   Shared_bool::movie_Status_Changed = false;
  }
 }
 //Resets all of the animation variables and booleans.
 else if (yes) {
  incremental_Lerp = 0;
  play->setSize(2.5);
  play->setColor(sf::Color(255, 255, 255, 0));
  yes = false;
 }
}/*--(Play_Pause_Active_Icon END)--*/

void Main_Runtime_Check::Popout_Window_PollEvent(Resized &re) {
 while (Shared_sf::second_Window.pollEvent(Shared_sf::second_Event)) {
  switch (Shared_sf::second_Event.type) {
  case sf::Event::Closed:
   /////////////////////////////////////////////////////////////////
   // If the "Popout" window is closed it will just resume from its 
   // default position on the main window
   /////////////////////////////////////////////////////////////////
   Shared_bool::second_Movie_Popout = false;
   Shared_sfe::movie2->setScale(Shared_sf::window.getSize().x / (Shared_sf::window.getSize().x * 2.f),
	Shared_sf::window.getSize().y / (Shared_sf::window.getSize().y * 2.f));
   re.playResize();
   Shared_sf::second_Window.close();
   break;

  case sf::Event::Resized:
   //Uses the same functions for resizing as with the normal window
   re.playResize();
   Shared_sf::second_Window.setView(sf::View(sf::FloatRect(0, 0, (float)Shared_sf::second_Window.getSize().x, (float)Shared_sf::second_Window.getSize().y)));
   break;
  }
 }
}
