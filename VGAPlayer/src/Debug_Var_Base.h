#pragma once
#include <string>
#include <SFML\Graphics\Text.hpp>

class debug_Base {
private:
 sf::Text Variable_Name;
 sf::Text value;
public:
 virtual void* get_Data() { return 0; }

 virtual void make_Debuggable(std::string get_Name) {}
 virtual std::string getName() { return ""; }

 virtual void set_Data(int &v) {}
 virtual void set_Data(float &v) {}
 virtual void set_Data(bool &v) {}
 virtual void set_Data(char &v) {}

 virtual sf::Text& get_Variable_Name() { return Variable_Name; }
 virtual sf::Text& get_Value() { return value; }
 virtual std::string get_Written_Value() { return ""; }
 virtual void set_ID(const char* c) {}
 virtual std::string get_ID() { return ""; }
};