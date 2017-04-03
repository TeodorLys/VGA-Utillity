#pragma once

#include <string>

class Settings
{
public:
	Settings();
	~Settings();
	void SetupStuff();
	///Not WHAT THAT FUCK, its: what to find
	bool findBool(std::string &b);
};

