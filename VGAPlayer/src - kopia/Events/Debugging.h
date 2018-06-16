#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include "Objects\Debug_Variable.h"

class Debugging {
public:
 std::string value = "0";
 int convValue = 0;
 float convValueF = 0;
 bool convValueB = 0;
 bool initialWrite = false;
 bool writing = false;
 sf::Text *write;
 sf::RectangleShape bg;
private:
 std::string limitList = "1234567890.";   //Debug
 sf::RenderWindow *window;
 sf::Mouse *mouse;
 sf::Event *event;
 sf::Font *sys;
 std::vector<Debug_Variable> debug_Vars;
 float biggest_Text = 0;
 int index = 0;
 float bg_X = 0;
public:
 Debugging(sf::RenderWindow &w, sf::Mouse &m, sf::Event &ev, sf::Font &font);
 void Add_Debug_Variables(Debug_Variable&);
 void Setup();
 void setPosition(sf::Vector2f a);
 void valueField();
 void Choose_Write();
 void Change_Write(bool);
 void draw();
};

