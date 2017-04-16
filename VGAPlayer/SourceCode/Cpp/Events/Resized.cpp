#include "Resized.h"
#include "GlobalVariables.h"

using namespace std;
using namespace GV;

void Resized::playResize() {

		//Fits the smaller movie the the resized window size
	if (mod.oneMovie->switchON)
		sfemov.movie2.fit(0, 0, (float)sfm.window.getSize().x, (float)sfm.window.getSize().y);

		//Corrects for the resized window size
	if (mod.oneMovie->switchON)
		sfemov.movie2.setPosition(sfm.window.getSize().x / 2, sfemov.movie.getPosition().y);

		//Fits the "Fullscreen" movie for the resized window size
		sfemov.movie.fit(0.f, 0.f, (float)sfm.window.getSize().x, (float)sfm.window.getSize().y);

		//Volume indicator for the resized window
		sfm.vol2.setPosition(sfm.window.getSize().x - 60.f, 0);

		sfm.tTimer.setPosition(0, sfm.window.getSize().y - sfm.tTimer.getGlobalBounds().height);
		sfm.smalltTimer.setPosition(sfm.window.getSize().x - sfm.smalltTimer.getGlobalBounds().width, sfm.window.getSize().y - sfm.smalltTimer.getGlobalBounds().height);
}

void Resized::menuResize() {
	sfm.theCrew.setPosition((float)sfm.window.getSize().x / 2, 300);

	//Size correction for the TEMP background
	sfm.b.setSize(sf::Vector2f((float)sfm.window.getSize().x, (float)sfm.window.getSize().y));

	//Menu PLAY button Scaling
	mod.play->ScreenScaleing(sf::Vector2f(sfm.window.getSize().x / 2.f, sfm.window.getSize().y - 100.f), 2, 2, 7 + (float)(mod.play->newScaleX));

	//"Loads Fullscreen movie" button Scaling
	mod.ffstv->ScreenScaleing(sf::Vector2f(mod.play->getNew() * 200.f - 200.f, sfm.window.getSize().y - 100.f), 1, 1, 5);

	//"Load the Smaller movie" button Scaling 
	mod.film->ScreenScaleing(sf::Vector2f(sfm.window.getSize().x - (mod.play->getNew() * 200.f - 200.f), sfm.window.getSize().y - 100.f), 1, 1, 5);

	mod.oneMovie->setPosition(sf::Vector2f(mod.play->getPosition().x, mod.play->getPosition().y - (mod.play->getSize().y)));

}
