#pragma once

#include "SABase.h"

class SAFloat : public base {
private:
	std::string saveName;
	float Fvalue = 0.f;
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

	void getV(float &f) {
		f = Fvalue;
	}

	void setV(float f) {
		Fvalue = f;
	}

	std::string getSave() {
		return(saveName + " = " + std::to_string(Fvalue));
	}

};