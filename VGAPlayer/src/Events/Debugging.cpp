#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\Text.hpp>
#include "Logger.h"
#include "Objects\Debug_Variable.h"
#include "Debugging.h"

using namespace std;

Debugging::Debugging(sf::RenderWindow &w, sf::Mouse &m, sf::Event &ev, sf::Font &font)
                     : window(&w), mouse(&m), event(&ev), sys(&font) {
 bg.setPosition(sf::Vector2f((float)mouse->getPosition(*window).x, (float)mouse->getPosition(*window).y));
 bg.setFillColor(sf::Color(50, 50, 50, 100));
 bg.setOutlineColor(sf::Color(70, 70, 70, 100));
 bg.setOutlineThickness(5.f);
}

void Debugging::Add_Debug_Variables(Debug_Variable &dv) {
 debug_Vars.push_back(dv);
}


void Debugging::setPosition(sf::Vector2f a) {
 bg.setPosition(a);   //Sets the position of the SFML object

 float y = 0;   //A temporary save variable

 for (size_t a = 0; a < debug_Vars.size(); a++) {
  if (a != 0)
   y = bg.getPosition().y + (debug_Vars[0].Variable_Name.getGlobalBounds().height + 10) * a ;
  else
   y = bg.getPosition().y;

  debug_Vars[a].Variable_Name.setPosition(sf::Vector2f(bg.getPosition().x, y));
  debug_Vars[a].value.setPosition(sf::Vector2f(debug_Vars[a].Variable_Name.getPosition().x + biggest_Text - 20, debug_Vars[a].Variable_Name.getPosition().y));
 }
}


//Basically a constructor, but needs to be called after viewport settings
void Debugging::Setup() {
 //Sets up the sf::Text object for the variable name.
 for (size_t a = 0; a < debug_Vars.size(); a++) {
  debug_Vars[a].Variable_Name.setFont(*sys);
  debug_Vars[a].Variable_Name.setString(debug_Vars[a].getName());
  debug_Vars[a].Variable_Name.setCharacterSize(25);
  debug_Vars[a].Variable_Name.setPosition(sf::Vector2f(bg.getPosition().x, bg.getPosition().y));
  
  //Just for esthetic purpose, changes the distance between Variable_Name and the Value
  if (debug_Vars[a].Variable_Name.getGlobalBounds().width > biggest_Text)
   biggest_Text = debug_Vars[a].Variable_Name.getGlobalBounds().width + 50;
 
  debug_Vars[a].value.setFont(*sys);
  debug_Vars[a].value.setString("0");
  debug_Vars[a].value.setCharacterSize(25);
  debug_Vars[a].value.setPosition(sf::Vector2f(biggest_Text - 20, debug_Vars[a].Variable_Name.getPosition().y));
 }

 debug_Vars[0].value.setFillColor(sf::Color(0, 255, 0));  //Selects the first variable

 //Changes the background based on the longest variable name
 bg.setSize(sf::Vector2f(biggest_Text, (30 * (float)debug_Vars.size())));  
 bg_X = bg.getSize().x;
}


void Debugging::Change_Write(bool b) {
 for (size_t a = 0; a < debug_Vars.size(); a++) {
  if (debug_Vars[a].value.getFillColor().r == 0 && debug_Vars[a].value.getFillColor().b == 0) {
   debug_Vars[a].value.setFillColor(sf::Color(255, 255, 255));
   if (b) {
	debug_Vars[a + 1].value.setFillColor(sf::Color(0, 255, 0));
   }
   else {
	debug_Vars[a - 1].value.setFillColor(sf::Color(0, 255, 0));
   }
   Choose_Write();
   break;
  }
 }
}


//Changes the selected value to edit
void Debugging::Choose_Write() {
 for (size_t a = 0; a < debug_Vars.size(); a++) {
  if (debug_Vars[a].value.getFillColor().r == 0 && debug_Vars[a].value.getFillColor().b == 0) {
   write = &debug_Vars[a].value;
   index = a;
   break;
  }
 }
}



void Debugging::valueField() {
 if (!initialWrite) {
  Choose_Write();
  initialWrite = true;
 }

 if (event->type == sf::Event::TextEntered) {
  if (event->text.unicode == 8 && debug_Vars[index].written_Value.size() > 0) {
   debug_Vars[index].written_Value.pop_back();
  }
  else if (event->text.unicode == 13) {
   initialWrite = false;

   if (debug_Vars[index].written_Value.size() > 0) {
	writing = false;
	for (size_t a = 0; a < debug_Vars.size(); a++) {
	 if (debug_Vars[a].get_ID() == "int") {
	  convValue = stoi(debug_Vars[a].written_Value.c_str());
	  debug_Vars[a].set_Data<int>(convValue);
	  //print.Log_Info("Debug_Window, Entered: %i, To: %s", convValue, debug_Vars[a].getName().c_str());
	 }
	 else if (debug_Vars[a].get_ID() == "float") {
	  convValueF = stof(debug_Vars[a].written_Value.c_str());
	  debug_Vars[a].set_Data<float>(convValueF);
	  //print.Log_Info("Debug_Window, Entered: %f, To: %s", convValueF, debug_Vars[a].getName().c_str());
	 }
	 else if (debug_Vars[a].get_ID() == "bool") {
	  convValueB = static_cast<bool>(stoi(debug_Vars[a].written_Value.c_str()));
	  debug_Vars[a].set_Data<bool>(convValueB);
	  //print.Log_Info("Debug_Window, Entered: %b, To: %s", convValueB, debug_Vars[a].getName().c_str());
	 }
	}
   }
   else {
	writing = false;
	convValue = 0;
   }
  }
  else {
			if (limitList.find((char)event->text.unicode) != string::npos && debug_Vars[index].written_Value.size() <= 10) {
				debug_Vars[index].written_Value.push_back((char)event->text.unicode);
			}
  }
  write->setString(debug_Vars[index].written_Value);
  if(write->getString().getSize() > 0 || event->key.code == 8 && write->getString().getSize() > 1)
  bg.setSize(sf::Vector2f(bg_X + (write->getGlobalBounds().width - 10), bg.getSize().y));
 }
 else if (event->type == sf::Event::KeyPressed) {
  if (event->key.code == sf::Keyboard::Down && debug_Vars.size() != 0 && (size_t)index < debug_Vars.size() && debug_Vars.size() > 1) {
   Change_Write(true);
  }
  else if (event->key.code == sf::Keyboard::Up && index != 0) {
   Change_Write(false);
  }
 }
}

void Debugging::draw() {
 window->draw(bg);
 for (Debug_Variable t : debug_Vars) {
  window->draw(t.Variable_Name);
  window->draw(t.value);
 }
}