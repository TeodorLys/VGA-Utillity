#include "GlobalVariables.h"
#include <fstream>
#include <Windows.h>

namespace GV {
	std::fstream settings;   //Settings file
	POINT firstPos;   //Mouse position over the first VLC window/any player
	POINT secondPos;   //Mouse position over the second window
	///Could probably have the paths in the settings file, but not now
	std::fstream path;   //the path.txt file
	int msg;   //The message box variable
	std::string font;   //the font path
	bool hideWindow;   //If you want to hide program when play/pauseing the players
}
