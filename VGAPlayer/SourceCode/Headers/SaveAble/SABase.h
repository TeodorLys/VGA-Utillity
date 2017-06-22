#pragma once

#include <string>
#include <iostream>

class base {
public:
	virtual void setV(bool b){}
	virtual void setV(std::string s) {}
	virtual void setV(int i){}
	virtual void setV(float f) {}

	virtual void getV(bool &b){}
	virtual void getV(std::string &s){}
	virtual void getV(int &i) {}
	virtual void getV(float &f) {}
	
	virtual std::string getName() { return "";}
	virtual void setName(std::string &s) {}
	virtual std::string getSave() { return ""; }
};
