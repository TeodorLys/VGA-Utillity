#pragma once

#include "SABase.h"

class SAFloat : public base {
private:
	std::string saveName;
	float Fvalue = 0.f;
	char var_Sign = 'f';
public:
	SAFloat(std::string name, float f) {
		saveName = name;
		Fvalue = f;
	}

	std::string getName() {
		return saveName;
	}

	void setName(std::string &s) {
		saveName = s;
	}

	float getV(float f) {
		return Fvalue;
	}

	void setV(float f) {
		Fvalue = f;
	}

	std::string getSave() {
		return(saveName + " = " + std::to_string(Fvalue));
	}

	char get_Var_Sign() {
	 return var_Sign;
	}
};