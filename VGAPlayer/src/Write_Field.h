#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Window\Event.hpp>

class Write_Field {
public:
 bool is_Writing = false;
 bool has_Written = false;
 std::string field_Value;
 int entered_Hour;

private:
 const std::string limitList = "1234567890.-";   //Debug
 const std::string letter_Limit_List = "1234567890.-smh";
 sf::RectangleShape field_To_Write;
 sf::Text writing_Object;
 sf::Color field_To_Write__Color;
 sf::Color field_To_Write__OutColor;
 sf::Color writing_Object__Color;
 float converted_Value;
 int entered_Second;
 int entered_Minute;
 bool initial_Setting = false;
 bool Addition_Timer = false;
 bool Subtraction_Timer = false;
 bool Letter_Timer = false;

public:
 static Write_Field& write() { static Write_Field Jump; return Jump; }
 Write_Field();
 sf::Vector2f Write_Field::getSize();
 void value_Field(sf::Event *event);
 void Draw();
 void setPosition(float x, float y);
 void setOpacity(int AlphaColor);
 bool Is_Invisible();
 sf::Color getColor();

private:
 void Regular_Time_Enter();
 void Letter_Time_Enter();
};
