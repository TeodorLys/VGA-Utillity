#include "GlobalVariables.h"
#include <fstream>
#include <Windows.h>

namespace GV {
	std::fstream settings;
	POINT firstPos;
	POINT secondPos;
	///Open/Creates the path.txt file, that includes the path of VLC player
	std::fstream path;
	int msg;
	std::string font;
	bool hideWindow;
}