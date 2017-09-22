#include "Logger.h"
#include <stdio.h>

using namespace std;

string get_Bool(int a) {
 if (a)
  return "true";
 else
  return "false";
}

Logger::Logger(){
 GetConsoleScreenBufferInfo(h_Std_Out, &csbi);
}

void Logger::Set_Level(int level) {
 Logger_Level = level;
}

void Logger::Log_Info(string s, ...) {
 if (Logger_Level == 0 && s != "") {
  b = s;
  buff = s;
  if (buff.find("%") != string::npos) {
   buff.erase(b.find_first_of("%"), b.length());

   bool foundPer = false;

   va_list vl;
   va_start(vl, s);

   for (size_t a = b.find_first_of("%"); a < b.length(); a++) {
	if (b[a] != '%') {
	 if (foundPer) {
	  switch (b[a]) {
	  case 's':
	   buff += va_arg(vl, char*);
	   break;
	  case 'i':
	   buff += to_string(va_arg(vl, int));
	   break;
	  case 'f':
	   buff += to_string(va_arg(vl, double));
	   break;
	  case 'b':
	   buff += get_Bool(va_arg(vl, bool));
	   break;

	  default:
 SetConsoleTextAttribute(h_Std_Out, RED);
 FlushConsoleInputBuffer(h_Std_In);
	  printf("[ERROR]: Given variable was not recognized");
 SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes
	   break;
	  }
	  foundPer = false;
	 }
	 else {
	  buff += b[a];
	 }
	}
	else {
	 foundPer = true;
	}
   }
   va_end(vl);
  }
  printf("[INFO]: %s\n", buff.c_str());
 }
}

void Logger::Log_Success(string s, ...) {
 if (Logger_Level == 0 && s != "") {
  SetConsoleTextAttribute(h_Std_Out, GREEN);
  FlushConsoleInputBuffer(h_Std_In);

  b = s;
  buff = s;
  if (buff.find("%") != string::npos) {
   buff.erase(b.find_first_of("%"), b.length());

   bool foundPer = false;

   va_list vl;
   va_start(vl, s);

   for (size_t a = b.find_first_of("%"); a < b.length(); a++) {
	if (b[a] != '%') {
	 if (foundPer) {
	  switch (b[a]) {
	  case 's':
	   buff += va_arg(vl, char*);
	   break;
	  case 'i':
	   buff += to_string(va_arg(vl, int));
	   break;
	  case 'f':
	   buff += to_string(va_arg(vl, double));
	   break;
	  case 'b':
	   buff += get_Bool(va_arg(vl, bool));
	   break;

	  default:
SetConsoleTextAttribute(h_Std_Out, RED);
FlushConsoleInputBuffer(h_Std_In);
	  printf("[ERROR]: Given variable was not recognized");
    SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes
	   break;
	  }
	  foundPer = false;
	 }
	 else {
	  buff += b[a];
	 }
	}
	else {
	 foundPer = true;
	}
   }
   va_end(vl);
  }
  printf("[SUCCESS]: %s\n", buff.c_str());

  SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes);
 }
}

void Logger::Log_Warning(string s, ...) {
 if (Logger_Level < 2 && s != "") {
 SetConsoleTextAttribute(h_Std_Out, YELLOW);
 FlushConsoleInputBuffer(h_Std_In);

 b = s;
 buff = s;
 if (buff.find("%") != string::npos) {
  buff.erase(b.find_first_of("%"), b.length());

  bool foundPer = false;

  va_list vl;
  va_start(vl, s);

  for (size_t a = b.find_first_of("%"); a < b.length(); a++) {
   if (b[a] != '%') {
	if (foundPer) {
	 switch (b[a]) {
	 case 's':
	  buff += va_arg(vl, char*);
	  break;
	 case 'i':
	  buff += to_string(va_arg(vl, int));
	  break;
	 case 'f':
	  buff += to_string(va_arg(vl, double));
	  break;
	 case 'b':
	  buff += get_Bool(va_arg(vl, bool));
	  break;

	 default:
     SetConsoleTextAttribute(h_Std_Out, RED);
FlushConsoleInputBuffer(h_Std_In);
	  printf("[ERROR]: Given variable was not recognized");
    SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes);
	  break;
	 }
	 foundPer = false;
	}
	else {
	 buff += b[a];
	}
   }
   else {
	foundPer = true;
   }
  }
  va_end(vl);
 }
 printf("[WARNING]: %s\n", buff.c_str());

 SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes);
 }
}

void Logger::Log_Error(string s, ...) {
 if (Logger_Level < 3 && s != "") {
  SetConsoleTextAttribute(h_Std_Out, RED);
  FlushConsoleInputBuffer(h_Std_In);

  string b = s;
  string buff = s;
  if (buff.find("%") != string::npos) {
   buff.erase(b.find_first_of("%"), b.length());

   bool foundPer = false;

   va_list vl;
   va_start(vl, s);

   for (size_t a = b.find_first_of("%"); a < b.length(); a++) {
	if (b[a] != '%') {
	 if (foundPer) {
	  switch (b[a]) {
	  case 's':
	   buff += va_arg(vl, char*);
	   break;
	  case 'i':
	   buff += to_string(va_arg(vl, int));
	   break;
	  case 'f':
	   buff += to_string(va_arg(vl, double));
	   break;
	  case 'b':
	   buff += get_Bool(va_arg(vl, bool));
	   break;

	  default:
	   SetConsoleTextAttribute(h_Std_Out, RED);
FlushConsoleInputBuffer(h_Std_In);
	  printf("[ERROR]: Given variable was not recognized");
    SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes
	   break;
	  }
	  foundPer = false;
	 }
	 else {
	  buff += b[a];
	 }
	}
	else {
	 foundPer = true;
	}
   }
   va_end(vl);
  }
  printf("[ERROR]: %s\n", buff.c_str());

  SetConsoleTextAttribute(h_Std_Out, csbi.wAttributes);
 }
}