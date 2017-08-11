#include "Play_Pause_Icon.h"
#include "../Shared/Shared_sfml_Objects.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Transform.hpp>
#include "../src/Logger.h"

using namespace std; // Consider removing this...

Play_Pause_Icon::Play_Pause_Icon() {
 PauseShape[0].setSize(sf::Vector2f(10, 50));
 PauseShape[0].setOrigin(PauseShape[0].getGlobalBounds().width / 2, PauseShape[0].getGlobalBounds().height / 2);
 PauseShape[1].setOrigin(PauseShape[0].getGlobalBounds().width / 2, PauseShape[0].getGlobalBounds().height / 2);
 PauseShape[1].setSize(sf::Vector2f(10, 50));
 PauseShape[1].setFillColor(sf::Color(255, 255, 255, 255 / 2));
 PauseShape[0].setFillColor(sf::Color(255, 255, 255, 255 / 2));
 

 playShape.setPointCount(3);
 playShape.setPoint(0, sf::Vector2f(0, 0));
 playShape.setPoint(1, sf::Vector2f(0, 50));
 playShape.setPoint(2, sf::Vector2f(30, 25));
 playShape.setOrigin(playShape.getGlobalBounds().width / 2, playShape.getGlobalBounds().height / 2);
 playShape.setFillColor(sf::Color(255, 255, 255, 0));
 background.setPointCount(50);
 background.setRadius(50);
 background.setFillColor(sf::Color(255, 255, 255, 255 / 2));
 background.setOrigin(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2);

 setPosition(static_cast<float>(Shared_sf::window.getSize().x) / 2, static_cast<float>(Shared_sf::window.getSize().y) / 2);
}
//Private rectangle position, wierd one...
void Play_Pause_Icon::setRectPosition(float x, float y) {
 PauseShape[0].setPosition(sf::Vector2f(x - PauseShape[0].getGlobalBounds().width, y));
 PauseShape[1].setPosition(sf::Vector2f(x + PauseShape[1].getGlobalBounds().width, y));
}

void Play_Pause_Icon::Update_Rect_Position() {
 PauseShape[0].setPosition(sf::Vector2f(background.getPosition().x - PauseShape[0].getGlobalBounds().width, background.getPosition().y));
 PauseShape[1].setPosition(sf::Vector2f(background.getPosition().x + PauseShape[1].getGlobalBounds().width, background.getPosition().y));
}

void Play_Pause_Icon::setPosition(float x, float y) {
 background.setPosition(x, y);
 setRectPosition(background.getPosition().x, background.getPosition().y);
 playShape.setPosition(background.getPosition());
}

void Play_Pause_Icon::setSize(float both) {
 background.setScale(both, both);
 playShape.setScale(both, both);
 PauseShape[0].setScale(both, both);
 PauseShape[1].setScale(both, both);
 Update_Rect_Position();
}

float Play_Pause_Icon::getSize() {
 return(background.getScale().x);
}

sf::Color Play_Pause_Icon::getColor() {
 return background.getFillColor();
}

void Play_Pause_Icon::setColor(sf::Color c) {
 background.setFillColor(c);
 if(!is_Paused)
 playShape.setFillColor(c);
 else {
  PauseShape[0].setFillColor(c);
  PauseShape[1].setFillColor(c);
 }
}

bool Play_Pause_Icon::set_Paused(bool b) {
 is_Paused = b;
 return b;
}

void Play_Pause_Icon::show_Paused() {
 if (is_Paused) {
  playShape.setFillColor(sf::Color(255, 255, 255, 0));
  PauseShape[0].setFillColor(sf::Color(255, 255, 255, 255));
  PauseShape[1].setFillColor(sf::Color(255, 255, 255, 255));
 }
 else {
  playShape.setFillColor(sf::Color(255, 255, 255, 255));
  PauseShape[0].setFillColor(sf::Color(255, 255, 255, 0));
  PauseShape[1].setFillColor(sf::Color(255, 255, 255, 0));
 }
}

void Play_Pause_Icon::Draw() {
 Shared_sf::window.draw(background);
 if (is_Paused) {
  Shared_sf::window.draw(PauseShape[0]);
  Shared_sf::window.draw(PauseShape[1]);
 }
 else {
  Shared_sf::window.draw(playShape);
 }
}