#pragma once
#include <string>
#include <SFML\Graphics\Text.hpp>

class Debug_Variable {
public:
 sf::Text Variable_Name;
 sf::Text value;
 std::string written_Value = "0";
 void* data;
 std::string id = "NULL";
private:
 std::string name;
public:
void make_Debuggable(std::string get_Name) { name = get_Name; }

std::string getName() { return name; }

template<class T>
void init_Data(T &v) { data = &v; }

template<class T>
void set_Data(T &v) { *(T*)data = v; }

template<class T>
T get_Data() { return *(T*)data; }

//sf::Text& get_Variable_Name() { return Variable_Name; }
//sf::Text& get_Value() { return value; }
std::string get_Written_Value() { return written_Value; }
void set_ID(const char* c) { id = c; }
std::string get_ID() { return id; }
};

