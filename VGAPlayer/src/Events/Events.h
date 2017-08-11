#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\System\Time.hpp>

class keyPress;
class Resized;
class InitialSetup;
class mouseEvent;
class movBase;
class Audio;

class Events {
private:
	keyPress* kp;
	Resized* re;
	InitialSetup* initial;
	mouseEvent* me;
	movBase** movie;
	Audio *_audio;
	int window_Pos_X;
	int window_Pos_Y;
	long saved_Style;
protected:
	float newWidth;
	float newHeight;
	bool changeStyle = false;	
public:
	Events(keyPress*, Resized*, InitialSetup*, mouseEvent*, movBase**, Audio*);
	void startMovies();
	void checkKeypress(sf::Event event);
	void SaveSettings();
	void startSecondMovie();
	void enterFullscreen(sf::RenderWindow &window);
	void exitFullscreen(sf::RenderWindow &window);
};
