#pragma once

#include "SaveAble.h"
#include "Logger.h"
#include <algorithm>
#include <vector>
#include <fstream>

class SaveSettings {
public:

 std::vector<base*> SA;

 //Save the "SaveAble Variables" to a parseable format.
 void saveVariable(base &b, std::fstream &f) {
  std::string buff = b.getName();
  Logger::log().Log_Info("Name:   %s", buff.c_str());
  if (!islower(buff[0]) || !isupper(buff[1])) {
   std::transform(buff.begin(), buff.begin() + 1, buff.begin(), ::toupper);
   buff = b.get_Var_Sign() + buff;
  }
  b.setName(buff);
  f << b.getSave() << std::endl;
  Logger::log().Log_Info("Value:  %s\n", b.getSave().c_str());
  SA.push_back(&b);
 }

 //Load the settings to the custom variables
 void Load_Settings(std::fstream &f) {
  int a = 0;
  std::string b;
  std::string strI;
  int I = 0;
  float F;
  for (std::string s; std::getline(f, s);) {
   switch (s[0]) {
   case 'b':
	SA[a]->setV(get_Bool_Value(s));
	break;

   case 's':
	b = s;
	b.erase(0, b.find_last_of("=") + 2);
	SA[a]->setV(b);
	break;

   case 'i':
	strI = s;
	strI.erase(0, strI.find_last_of(" = ") + 1);
	I = atoi(strI.c_str());
	SA[a]->setV(I);
	break;

   case 'f':
	strI = s;
	strI.erase(0, strI.find_last_of(" = ") + 1);
	F = std::stof(strI.c_str());
	SA[a]->setV(F);
	break;

   default:
	Logger::log().Log_Error("Variable %s was not loaded correctly", s.c_str());
	break;
   }
   a++;
  }
 }

 //Example: Returns true if string says "true"
 bool get_Bool_Value(std::string &s) {
  if (s.find("true") != std::string::npos)
   return true;
  else
   return false;
 }

 //Sends the loaded variables into a "global" vector, for later settings.
 void Load(base &i) {
  SA.push_back(&i);
 }
};