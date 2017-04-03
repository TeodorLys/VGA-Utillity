#pragma once

#include <fstream>
#include <Windows.h>

namespace GV {
	extern std::fstream settings;
	extern 	POINT firstPos;
	extern POINT secondPos;
	extern std::fstream path;
	extern int msg;
	extern std::string font;
	extern bool hideWindow;
}