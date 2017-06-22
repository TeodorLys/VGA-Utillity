#pragma once

#include "SABase.h"

class SAString : public base {
private:
	std::string saveName;
	std::string strValue;
public:
	SAString(std::string name, std::string str) {
		saveName = name;
		strValue = str;
	}

	void getV(std::string &s) {
		s = strValue;
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
};
