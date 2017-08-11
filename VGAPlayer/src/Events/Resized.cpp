#include "Resized.h"
#include "../InitialSetup.h"
#include "../Shared/Shared_sfml_Objects.h"
#include "../Shared/Shared_sfe_Movie.h"
#include "../Shared/Shared_Modules.h"
#include "../Objects/Buttons.h"
#include "../Objects/Switch.h"
#include <sfeMovie\Movie.hpp>

using namespace std;
//using namespace GV;

Resized::Resized(InitialSetup* initial_Object) : initial(initial_Object) {}

void Resized::playResize() {
 //Fits the smaller movie the the resized window size
 if (Shared_Mod::oneMovie->switchON) {
  Shared_sfe::movie2->fit(0, 0, (float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y);
  Shared_sfe::movie2->setPosition((float)Shared_sf::window.getSize().x / 2, (float)Shared_sfe::movie->getPosition().y);
  Shared_Mod::secondReplay->setPosition(sf::Vector2f((float)Shared_sf::window.getSize().x / 2, (float)Shared_sf::window.getSize().y - 100.f), 5);
 }
 //Fits the "Fullscreen" movie for the resized window size
 Shared_sfe::movie->fit(0.f, 0.f, (float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y);

 playMenuResize();
}

void Resized::playMenuResize() {
 //Volume indicator for the resized window
 //Volume 1 does not need to be resized because it is on 0,0
 Shared_sf::vol2.setPosition(Shared_sf::window.getSize().x - 60.f, 0);

 Shared_sf::tTimer.setPosition(0, Shared_sf::window.getSize().y - Shared_sf::tTimer.getGlobalBounds().height);
 Shared_sf::smalltTimer.setPosition(Shared_sf::window.getSize().x - Shared_sf::smalltTimer.getGlobalBounds().width - 20, Shared_sf::window.getSize().y - Shared_sf::smalltTimer.getGlobalBounds().height);
}

void Resized::menuResize() {
 Logger::log().Log_Info("X: %i Y: %i", Shared_sf::window.getSize().x, Shared_sf::window.getSize().y);
 Shared_sf::theCrew.setPosition((float)Shared_sf::window.getSize().x / 2, 300);

 //Size correction for the background
 Shared_sf::b.setSize(sf::Vector2f((float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y));

 //Menu PLAY button Scaling
 Shared_Mod::play->ScreenScaleing(sf::Vector2f(Shared_sf::window.getSize().x / 2.f, Shared_sf::window.getSize().y - 100.f), 2, 2, 7 + (float)(Shared_Mod::play->newScaleX));

 //"Loads Fullscreen movie" button Scaling
 Shared_Mod::ffstv->ScreenScaleing(sf::Vector2f(Shared_Mod::play->getNew() * 200.f - 200.f, Shared_sf::window.getSize().y - 100.f), 1, 1, 5);

 //"Load the Smaller movie" button Scaling 
 Shared_Mod::film->ScreenScaleing(sf::Vector2f(Shared_sf::window.getSize().x - (Shared_Mod::play->getNew() * 200.f - 200.f), Shared_sf::window.getSize().y - 100.f), 1, 1, 5);

 //One Movie switch Scaling
 Shared_Mod::oneMovie->setPosition(sf::Vector2f(Shared_Mod::play->getPosition().x, Shared_Mod::play->getPosition().y - (Shared_Mod::play->getSize().y)));
}