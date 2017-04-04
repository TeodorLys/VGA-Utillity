// VGAPlayer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InitialSetup.h"
#include "GlobalVariables.h"
#include <SFML\Graphics.hpp>
#include <sfeMovie\Movie.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>



#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else 
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#endif // _DEBUG

using namespace std;
using namespace GV;

void rendering(sf::RenderWindow *window);
void enterFullscreen(sf::RenderWindow &window);
void exitFullscreen(sf::RenderWindow &window);

bool focus;
bool init;
bool doonce;
bool dontonce = false;
int initx;
int inity;
bool isFullscreen = false;
LONG SavelStyle;
LONG SavelExStyle;
sf::RectangleShape shape;

int main() {

	sf::Mouse mouse;

	GV::init.movieWindow();
	GV::init.UI();

	//CRITICAL, SECOND THREAD
	window.setActive(false);
	sf::Thread t(rendering, &window);
	t.launch();
	//CRITICAL, SECOND THREAD
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::LostFocus) {
				focus = false;
			}
			else if (event.type == sf::Event::GainedFocus) {
				focus = true;
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Space:
					if (movie.getStatus() == sfe::Playing) {
						movie.pause();
						movie2.pause();
					}
					else {
						movie.play();
						movie2.play();
					}
					break;
				case sf::Keyboard::LAlt:
					if (!isFullscreen)
						enterFullscreen(window);
					else
						exitFullscreen(window);
					break;
				case sf::Keyboard::RAlt:
				default:
					break;
				}
			}
			else if (event.type == sf::Event::Resized) {
				movie2.fit(0, 0, window.getSize().x, window.getSize().y);
				movie2.setPosition(window.getSize().x / 2, 0);
				movie.fit(0, 0, window.getSize().x, window.getSize().y);
				window.setView(sf::View(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y)));
			}
		}
	}
}

//This is a second thread, which means that the videos will play even though you move or resize the window
void rendering(sf::RenderWindow *window) {

	while (window->isOpen()) {

		movie.update();
		movie2.update();

		window->clear();

		window->draw(movie);
		window->draw(movie2);

		window->display();
	}
}

void enterFullscreen(sf::RenderWindow &window) {
		LONG lStyle = GetWindowLong(window.getSystemHandle(), GWL_STYLE);
		SavelStyle = lStyle;
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
		SetWindowLong(window.getSystemHandle(), GWL_STYLE, lStyle);
		LONG lExStyle = GetWindowLong(window.getSystemHandle(), GWL_EXSTYLE);
		SavelExStyle = lExStyle;
		lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		SetWindowLong(window.getSystemHandle(), GWL_EXSTYLE, lExStyle);
		SetWindowPos(window.getSystemHandle(), HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		isFullscreen = true;
}

void exitFullscreen(sf::RenderWindow &window) {
		SetWindowLong(window.getSystemHandle(), GWL_STYLE, SavelStyle);
		SetWindowLong(window.getSystemHandle(), GWL_EXSTYLE, SavelExStyle);
		isFullscreen = false;
}
