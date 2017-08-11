#include <string>
#include <sfeMovie\Movie.hpp>
#include "../src/Events/Actions.h"
#include "Write_Field.h"
#include "Logger.h"
#include "../src/Shared/Shared_sfe_Movie.h"
#include "../src/Shared/Shared_sfml_Objects.h"
#include "../src/Shared/Shared_Variables.h"

using namespace std;

Write_Field::Write_Field() {
 writing_Object.setFont(Shared_sf::sysFont);
 writing_Object.setCharacterSize(50);
 writing_Object__Color = sf::Color(255, 255, 255 ,0);
 writing_Object.setFillColor(writing_Object__Color);
 field_Value = "";
 writing_Object.setString(field_Value);

 field_To_Write.setSize(sf::Vector2f(190, 50));
 field_To_Write.setOutlineThickness(3.f);

 field_To_Write__Color = sf::Color(50, 50, 50, 0);
 field_To_Write__OutColor = sf::Color(100, 100, 100, 0);

 field_To_Write.setFillColor(field_To_Write__Color);
 field_To_Write.setOutlineColor(field_To_Write__OutColor);
}


void Write_Field::Draw() {
 Shared_sf::window.draw(field_To_Write);
 Shared_sf::window.draw(writing_Object);
}


void Write_Field::setPosition(float x, float y) {
 field_To_Write.setPosition(sf::Vector2f(x, y));
 writing_Object.setPosition(sf::Vector2f(field_To_Write.getPosition().x + 4, field_To_Write.getPosition().y - 6));
}


sf::Vector2f Write_Field::getSize() {
 return field_To_Write.getSize();
}


bool Write_Field::Is_Invisible() {
 if (field_To_Write.getFillColor().a == 0 && writing_Object.getFillColor().a == 0) {
  return true;
  //Dont understand why I did this... -- but it works
  field_To_Write__Color = sf::Color(field_To_Write__Color.r, field_To_Write__Color.g,
									field_To_Write__Color.b, 255);

  field_To_Write.setFillColor(field_To_Write__Color);

  field_To_Write__OutColor = sf::Color(field_To_Write__OutColor.r, field_To_Write__OutColor.g,
									   field_To_Write__OutColor.b, 255);
  field_To_Write.setOutlineColor(field_To_Write__OutColor);

  writing_Object__Color = sf::Color(writing_Object__Color.r, writing_Object__Color.g, 
									writing_Object__Color.b, 255);
  writing_Object.setFillColor(writing_Object__Color);
 }
 else {
  return false;
 }
}


sf::Color Write_Field::getColor() {
 return field_To_Write.getFillColor();
}


void Write_Field::setOpacity(int AlphaColor) {
 field_To_Write__Color = sf::Color(field_To_Write__Color.r, field_To_Write__Color.g, 
								   field_To_Write__Color.b, AlphaColor);
 field_To_Write.setFillColor(field_To_Write__Color);

 field_To_Write__OutColor = sf::Color(field_To_Write__OutColor.r, field_To_Write__OutColor.g, 
									  field_To_Write__OutColor.b, AlphaColor);
 field_To_Write.setOutlineColor(field_To_Write__OutColor);

 writing_Object__Color = sf::Color(writing_Object__Color.r, writing_Object__Color.g, writing_Object__Color.b, AlphaColor);
 writing_Object.setFillColor(writing_Object__Color);
}


void Write_Field::value_Field(sf::Event *event) {
 if (event->type == sf::Event::TextEntered) {
  //print.Log_Info("Key: %i", static_cast<int>(Shared_sf::event.text.unicode));
  switch (event->text.unicode) {
  case 8:
   if (field_Value.size() > 0)
	field_Value.pop_back();
   break;

  case 13:
   if (field_Value.size() > 0) {
	is_Writing = false;
	initial_Setting = false;
	if (field_Value.size() == 8 && !Letter_Timer)
	 Regular_Time_Enter();
	else if (field_Value.size() == 8 && Letter_Timer)
	 Letter_Time_Enter();
	else
	 print.Log_Error("Values was entered incorrectly");
   }
   break;

  case 43:
   if (!Addition_Timer) {
	Addition_Timer = true;
	Subtraction_Timer = false;
	field_To_Write__OutColor = sf::Color(100, 255, 100, field_To_Write__OutColor.a);
	field_To_Write.setOutlineColor(field_To_Write__OutColor);
   }
   else {
	Addition_Timer = false;
	Subtraction_Timer = false;
	field_To_Write__OutColor = sf::Color(100, 100, 100, field_To_Write__OutColor.a);
	field_To_Write.setOutlineColor(field_To_Write__OutColor);
   }
   break;

  case 45:
   if (!Subtraction_Timer) {
	Addition_Timer = false;
	Subtraction_Timer = true;
	field_To_Write__OutColor = sf::Color(255, 100, 100, field_To_Write__OutColor.a);
	field_To_Write.setOutlineColor(field_To_Write__OutColor);
   }
   else {
	Addition_Timer = false;
	Subtraction_Timer = false;
	field_To_Write__OutColor = sf::Color(100, 100, 100, field_To_Write__OutColor.a);
	field_To_Write.setOutlineColor(field_To_Write__OutColor);
   }
   break;

  case 109:
   Letter_Timer = true;
   if(field_Value.size() == 0){
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
   }
   field_Value.push_back('m');
   break;

  case 104:
   Letter_Timer = true;
   if (field_Value.size() == 0) {
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
   }
   field_Value.push_back('h');
   break;

  case 115:
   Letter_Timer = true;
   if (field_Value.size() == 0) {
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
	field_Value.push_back(' ');
   }
   field_Value.push_back('s');
   break;

  default:
   if (field_Value.size() < 8)
	limitList.find((char)event->text.unicode) != string::npos ? field_Value.push_back((char)event->text.unicode) : 0;

   if (field_Value.size() % 3 == 2 && field_Value.size() < 8 && !Letter_Timer) {
	field_Value.push_back(':');
   }
   break;
  } // Switch end...
  if (field_Value.find("m") == string::npos && field_Value.find("s") == string::npos && field_Value.find("h") == string::npos && Letter_Timer) {
   Letter_Timer = false;
  }
  writing_Object.setString(field_Value);
 }
}

void Write_Field::Letter_Time_Enter() {
 string buff = field_Value;
 int iBuff = 0;
 float entered = 0;
 if (field_Value.find("m") != string::npos) {
  iBuff = Actions::stoint(buff);
  entered = static_cast<float>(iBuff * 60) + 0.01f;
  print.Log_Warning("Minute: %f", entered);
 }
 else if (field_Value.find("h") != string::npos) {
  iBuff = Actions::stoint(buff);
  entered = static_cast<float>((iBuff * 60) * 60) + 0.01f;
  print.Log_Warning("Hour: " + buff);
 }
 else if (field_Value.find("s") != string::npos) {
  entered = Actions::stoint(buff) + 0.01f;
  print.Log_Warning("Hour: %s", buff);
 }

 print.Log_Info("Entered:   %f", entered);

 if (Addition_Timer)
  Shared_sfe::movie->setPlayingOffset(Shared_sfe::movie->getPlayingOffset() + sf::seconds(entered));
 else if (Subtraction_Timer)
  Shared_sfe::movie->setPlayingOffset(Shared_sfe::movie->getPlayingOffset() - sf::seconds(entered));
 else
  Shared_sfe::movie->setPlayingOffset(sf::seconds((float)entered));

 field_Value = "";
}


void Write_Field::Regular_Time_Enter() {
  string buff;
  buff.append(field_Value, 0, 2);
  entered_Hour = stoi(buff);

  print.Log_Warning("Hour: " + buff);

  buff = "";
  buff.append(field_Value, 3, 2);
  entered_Minute = stoi(buff);

  print.Log_Warning("Minute: " + buff);

  buff = "";
  buff.append(field_Value, 6, 2);
  entered_Second = stoi(buff);

  print.Log_Warning("Second: " + buff);

  print.Log_Info("Entered: " + to_string(entered_Hour) + ", " + to_string(entered_Minute) + ", " + to_string(entered_Second));

  converted_Value = ((entered_Hour * 60) * 60) + (entered_Minute * 60) +
   entered_Second + 0.01f;  //must add 0.01 otherwise sfeMovie will crash... 

  print.Log_Warning("Convertion to Seconds: " + to_string(converted_Value));

  if (Addition_Timer)
   Shared_sfe::movie->setPlayingOffset(Shared_sfe::movie->getPlayingOffset() + sf::seconds(converted_Value));
  else if (Subtraction_Timer)
   Shared_sfe::movie->setPlayingOffset(Shared_sfe::movie->getPlayingOffset() - sf::seconds(converted_Value));
  else
   Shared_sfe::movie->setPlayingOffset(sf::seconds(converted_Value));

  field_Value = "";
}