#pragma once
#include "Events.h"
#include <chrono>

class mouseEvent : public Events {
private:
	void emptyPath();
	void loadMovieButtons();

public:
	void mouseWheel(sf::Event event);
	void menuButtons();
	void checkUI(std::chrono::high_resolution_clock::time_point &tStart, std::chrono::high_resolution_clock::time_point &tEnd);
	void showHideUI();

};

