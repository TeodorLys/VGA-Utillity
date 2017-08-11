#include "mouseEvent.h"
#include "Events.h"
#include "../Audio.h"
#include "../Events/Animation.h"
#include "../Events/Actions.h"
#include "../Shared/Shared_sfml_Objects.h"

using namespace std;

mouseEvent::mouseEvent(Events* e, Audio *Audio_Object) :
					   ev(e), _audio(Audio_Object){}

void mouseEvent::Initialize_Isolated_Movie(sfe::Movie &Movie_One, size_t &Hour,
								 size_t &Minute, size_t &Second){
 ev->startMovies();
 _audio->Initialize_First_Movie_Timer(Movie_One, Hour, Minute, Second);
}


////////////////////////////////////////////////////////////////////////////////////////////////
///Checks if the mouse is still, and are in Fullscreen mode
////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::checkUI(chrono::high_resolution_clock::time_point &tStart, 
						 chrono::high_resolution_clock::time_point &tEnd, 
						 int &mousePosY, int &mousePosX, int Mouse_Get_Position_X, 
						 int Mouse_Get_Position_Y) {

 if (Mouse_Get_Position_X == mousePosX && Mouse_Get_Position_Y == mousePosY || Actions::Is_Mouse_Within_Window(Shared_sf::window, Shared_sf::mouse)) {
  if (chrono::duration_cast<chrono::milliseconds>(tStart - tEnd).count() >= 2000) {
   mouseIsStill = true;
   mouseOnce = true;
  }
 } else {
  mouseIsStill = false;
  mousePosX = Mouse_Get_Position_X;
  mousePosY = Mouse_Get_Position_Y;
  tEnd = chrono::high_resolution_clock::now();
 }
 showHideUI();
}

void mouseEvent::set_Opacity_Info(sf::Uint8 alphaColor) {
 Shared_sf::vol1.setFillColor(sf::Color(Shared_sf::vol1.getFillColor().r, Shared_sf::vol1.getFillColor().g, Shared_sf::vol1.getFillColor().b, alphaColor));
 Shared_sf::vol2.setFillColor(sf::Color(Shared_sf::vol2.getFillColor().r, Shared_sf::vol2.getFillColor().g, Shared_sf::vol2.getFillColor().b, alphaColor));
 Shared_sf::smalltTimer.setFillColor(sf::Color(Shared_sf::smalltTimer.getFillColor().r, Shared_sf::smalltTimer.getFillColor().g, Shared_sf::smalltTimer.getFillColor().b, alphaColor));
 Shared_sf::tTimer.setFillColor(sf::Color(Shared_sf::tTimer.getFillColor().r, Shared_sf::tTimer.getFillColor().g, Shared_sf::tTimer.getFillColor().b, alphaColor));
}

////////////////////////////////////////////////////////////////////////////////////////////////
///When the mouse is still, Show/Hide UI. Only during fullscreen mode.
////////////////////////////////////////////////////////////////////////////////////////////////
void mouseEvent::showHideUI() {
 if (!mouseIsStill) {
  if (mouseOnce) {
   Shared_sf::window.setMouseCursorVisible(true);
   set_Opacity_Info(255);
   mouseOnce = false;
  }
 } else {
	 Shared_sf::window.setMouseCursorVisible(false);
	 set_Opacity_Info(Animation::Lerp_Opacity(Shared_sf::vol1.getFillColor().a, 10));
 }
}//ShowHideUI Function END
