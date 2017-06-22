#pragma once

#include "SABase.h"

class SAInt : public base {
private:
	std::string saveName;
	int iValue = 0;
public:
	SAInt(std::string name = "", int i = 0) {
		saveName = name;
		iValue = i;
	}

	void getV(int &i) {
		i = iValue;
	}

	void setV(int i) {
		iValue = i;
	}

	std::string getName() {
		return saveName;
	}

	void setName(std::string &s) {
		saveName = s;
	}

	std::string getSave() {
		return(saveName + " = " + std::to_string(iValue));
	}

};