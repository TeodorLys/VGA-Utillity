
#pragma once
#include <SFML\Window\Event.hpp>
#include <chrono>

class Events;
class Audio;
namespace sfe {
 class Movie;
};

class mouseEvent {
private: 
 bool mouseOnce    = false;
 bool mouseIsStill = false;

 Events *ev;
 Audio  *_audio;
public:
 mouseEvent(Events*, Audio *Audio_Object);
 void checkUI(std::chrono::high_resolution_clock::time_point &tStart,
			  std::chrono::high_resolution_clock::time_point &tEnd,
			  int &mousePosY, int &mousePosX, int Mouse_Get_Position_X,
			  int Mouse_Get_Position_Y);

 void showHideUI();
 void set_Opacity_Info(sf::Uint8);
 void Initialize_Isolated_Movie(sfe::Movie &Movie_One, size_t &Hour,
								size_t &Minute, size_t &Second);
};

