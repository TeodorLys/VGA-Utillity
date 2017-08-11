#pragma once
#include <windows.h>
#include <string>

class Logger {
public: 
  enum {
  LOG_INFO_LEVEL,
  LOG_WARN_LEVEL,
  LOG_ERROR_LEVEL
 };

private:
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 HANDLE h_Std_In  = GetStdHandle(STD_INPUT_HANDLE);
 HANDLE h_Std_Out = GetStdHandle(STD_OUTPUT_HANDLE);
 int Logger_Level = LOG_INFO_LEVEL;
 std::string buff;
 std::string b;
 enum {
  RED = 0x0C,
  YELLOW = 0x0E,
  GREEN = 0x0A
 };

public:
 static Logger& log() {
  static Logger log;
  return log;
 }

 Logger();
 void Set_Level(int level);
 void Log_Info(std::string, ...);
 void Log_Warning(std::string, ...);
 void Log_Error(std::string, ...);
 void Log_Success(std::string, ...);
};

#define print Logger::log()