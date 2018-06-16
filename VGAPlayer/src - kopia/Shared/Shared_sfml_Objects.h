#pragma once

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

namespace Shared_sf {
 extern sf::Event event;
 extern sf::Event second_Event;
 extern sf::Time off;
 extern sf::Font font;
 extern sf::Font sysFont;
 extern sf::Text OMov;
 extern sf::Text OVGA;
 extern sf::Text tPlay;
 extern sf::Text tTimer;
 extern sf::Text smalltTimer;
 extern sf::Text vol1;
 extern sf::Text vol2;
 extern sf::Texture base;
 extern sf::Texture theCrew_Texture;
 extern sf::RectangleShape b;
 extern sf::RectangleShape theCrew;
 extern sf::Color COMov;
 extern sf::Color COVGA;
 extern sf::RenderWindow window;
 extern sf::RenderWindow second_Window;
 extern sf::Mouse mouse;
};

