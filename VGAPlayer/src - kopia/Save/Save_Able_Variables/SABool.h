#pragma once

#include "SABase.h"

class SABool : public base {
private:
	std::string saveName;
	bool value;
	char var_Sign = 'b';
public:
	SABool(std::string name, bool v) {
		saveName = name;
		value = v;
	}

	std::string getName() {
		return saveName;
	}

	void setName(std::string &s) {
		saveName = s;
	}

	bool getV(bool b) {
	 return value;
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

	char get_Var_Sign() {
	 return var_Sign;
	}
};

