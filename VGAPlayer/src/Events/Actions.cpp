#include "InitialSetup.h"
#include "Actions.h"
#include "Shared\Shared_sfml_Objects.h"
#include <sfeMovie\Movie.hpp>
#include "Objects\Switch.h"
#include <iostream>
#include "Shared\Shared_sfe_Movie.h"

using namespace std;

float Actions::xLimit = 0;
float Actions::yLimit = 0;

Actions::Actions(InitialSetup* initial_Object) : initial(initial_Object){
}

//Hover Overloaded Function
bool Actions::Hover(sf::Text &t) {
	return(t.getGlobalBounds().contains(sf::Vector2f(Shared_sf::mouse.getPosition(Shared_sf::window))));
}

bool Actions::Hover(sf::RectangleShape &shape) {
	return(shape.getGlobalBounds().contains(sf::Vector2f(Shared_sf::mouse.getPosition(Shared_sf::window))));
}

bool Actions::Hover(sf::Sprite &s) {
	return(s.getGlobalBounds().contains(sf::Vector2f(Shared_sf::mouse.getPosition(Shared_sf::window))));
}

//Click function
bool Actions::Click() {
	return(Shared_sf::event.type == sf::Event::MouseButtonReleased);
}

bool Actions::DownClick() {
	return(Shared_sf::mouse.isButtonPressed(sf::Mouse::Left));
}

bool Actions::Movie_Two_Hover(sf::Mouse mouse, sf::RenderWindow &window, sfe::Movie &movie2) {
 return(mouse.getPosition(window).x > movie2.getPosition().x &&
		mouse.getPosition(window).x < movie2.getPosition().x + xLimit &&
		mouse.getPosition(window).y > movie2.getPosition().y &&
		mouse.getPosition(window).y < movie2.getPosition().y + yLimit);
}

void Actions::SetLimits(float LX, float LY) {
 xLimit = LX;
 yLimit = LY;
}

int Actions::ffstv() {
 srand(static_cast<unsigned int>(time(NULL)));
 int r = rand() % 4;
 return r;
}

bool Actions::Is_Mouse_Within_Window(sf::RenderWindow &window, sf::Mouse &mouse) {
 if (mouse.getPosition(window).x > (int)window.getSize().x || mouse.getPosition(window).y > (int)window.getSize().y) {
  return true;
 }
 else {
  return false;
 }
}

bool Actions::Mouse_Wheel_Moved() {
 return(Shared_sf::event.mouseWheel.delta > 0);
}

int Actions::stoint(const std::string s) {
 const string limit = "0123456789-";
 string buff;

 for (char c : s) {
  if (limit.find(c) != string::npos) {
   buff += c;
  }
 }
 int i = stoi(buff);

 print.Log_Info("STOINT: %i", i);

 return i;
}