#pragma once

#include "SABase.h"

class SAString : public base {
private:
	std::string saveName;
	std::string strValue;
	char var_Sign = 's';
public:
	SAString(std::string name, std::string str) {
		saveName = name;
		strValue = str;
	}

	std::string getV(char c) {
		return strValue;
	}

	void setV(std::string s) {
		strValue = s;
	}

	std::string getName() {
		return saveName;
	}

	void setName(std::string &s) {
		saveName = s;
	}

	std::string getSave() {
		return(saveName + " = " + strValue);
	}

	char get_Var_Sign() {
	 return var_Sign;
	}
};
