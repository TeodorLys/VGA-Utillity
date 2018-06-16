#pragma once

#include <string>

class base {
private:
 char var_Sign;
public:
	virtual void setV(bool b){}
	virtual void setV(std::string s) {}
	virtual void setV(int i){}
	virtual void setV(float f) {}

	virtual bool getV(bool b) { return 0; }
	virtual std::string getV(char c) { return ""; }
	virtual int getV(int a) { return 0; }
	virtual float getV(float f) { return 0.f; }
	
	virtual char get_Var_Sign() { return ' '; }

	virtual std::string getName() { return "";}
	virtual void setName(std::string &s) {}
	virtual std::string getSave() { return ""; }
};
