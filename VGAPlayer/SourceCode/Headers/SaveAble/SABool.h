#pragma once

#include "SABase.h"

class SABool : public base {
private:
	std::string saveName;
	bool value;
public:
	SABool(std::string name, bool v) {
		saveName = name;
		value = v;
	}

	std::string getName() {
		return saveName;
	}

	void setName(std::string &s) {
		s = saveName;
	}

	void getV(bool &b) {
		b = value;
	}

	void setV(bool b) {
		value = b;
	}

	std::string getBool() {
		if (value)
			return "true";
		else
			return "false";
	}

	std::string getSave() {
		return(saveName + " = " + getBool());
	}

};

