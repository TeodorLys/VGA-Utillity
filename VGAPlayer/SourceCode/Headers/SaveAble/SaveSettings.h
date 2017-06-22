#pragma once

#include "SaveAble.h"
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

class SaveSettings {
public:

	std::vector<base*> SA;

	//Save the saveable boolean to file
	void saveVariable(SABool &b, std::fstream &f) {
		std::string buff = b.getName();
		if (!islower(buff[0]) || !isupper(buff[1])) {
			std::transform(buff.begin(), buff.begin() + 1, buff.begin(), ::toupper);
			buff = "b" + buff;
		}
		b.setName(buff);
		f << b.getSave() << std::endl;
		SA.push_back(&b);
	}
	//Save the saveable integar to file
	void saveVariable(SAInt &i, std::fstream &f) {
		std::string buff = i.getName();
		if (!islower(buff[0]) || !isupper(buff[1])) {
			std::transform(buff.begin(), buff.begin() + 1, buff.begin(), ::toupper);
			buff = "i" + buff;
		}
		i.setName(buff);
		f << i.getSave() << std::endl;
		SA.push_back(&i);
	}
	//Save the saveable string to file
	void saveVariable(SAString &s, std::fstream &f) {
		std::string buff = s.getName();
		if (!islower(buff[0]) || !isupper(buff[1])) {
			std::transform(buff.begin(), buff.begin() + 1, buff.begin(), ::toupper);
			buff = "s" + buff;
		}
		s.setName(buff);
		f << s.getSave() << std::endl;
		SA.push_back(&s);
	}

	void saveVariable(SAFloat &fl, std::fstream &f) {
		std::string buff = fl.getName();
		if (islower(buff[0]) == false || isupper(buff[1]) == false) {
			std::transform(buff.begin(), buff.begin() + 1, buff.begin(), ::toupper);
			buff = "f" + buff;   
		}
		fl.setName(buff);
		f << fl.getSave() << std::endl;
		SA.push_back(&fl);
	}

	//Load the settings to the custom variables
	void loadSettings(std::fstream &f) {
		int a = 0;
		bool buff;
		std::string b;
		std::string strI;
		int I = 0;
		float F;
		for (std::string s; std::getline(f, s);) {
			switch (s[0]) {
			case 'b':
				buff = getBool(s);
				SA[a]->setV(buff);
				break;

			case 's':
				b = s;
				b.erase(0, b.find_last_of("=") + 2);
				std::cout << b << std::endl;
				SA[a]->setV(b);
				break;

			case 'i':
				strI = s;
				strI.erase(0, strI.find_last_of(" = ") + 1);
				I = atoi(strI.c_str());
				SA[a]->setV(I);
				break;
				
			case 'f':
				strI = s;
				strI.erase(0, strI.find_last_of(" = ") + 1);
				F = std::stof(strI.c_str());
				SA[a]->setV(F);
				break;

			default:
				break;
			}
			a++;
		}
	}

	//Returns true if string is "true"
	bool getBool(std::string &s) {
		if (s.find("true") != std::string::npos)
			return true;
		else
			return false;
	}

	//If when loading the settings I dont push back the variables
	void vecPush(SAInt &i) {
		SA.push_back(&i);
	}
	
	void vecPush(SABool &b) {
		SA.push_back(&b);
	}

	void vecPush(SAString &s) {
		SA.push_back(&s);
	}
	
	void vecPush(SAFloat &f) {
		SA.push_back(&f);
	}
};