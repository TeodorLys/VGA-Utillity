#pragma once

class InitialSetup;

class Resized {
private:
	InitialSetup* initial;
public:
	Resized(InitialSetup*);
	void playResize();
	void menuResize();
	void playMenuResize();
};

