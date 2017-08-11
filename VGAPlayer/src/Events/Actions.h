#pragma once
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Time.hpp>

class InitialSetup;

namespace sfe {
 class Movie;
};

namespace sf {
 class Mouse;
 class RenderWindow;
};

class Actions {
private:
 static float xLimit;
 static float yLimit;
 int r;
 int g;
 int b;
 sf::Color c = sf::Color(10, 10, 10);
 bool doonce = false;
 InitialSetup* initial;
public:
 Actions(InitialSetup*);
 static bool Hover(sf::Text &t);
 static bool Hover(sf::RectangleShape &shape);
 static bool Hover(sf::Sprite &s);
 static bool Click();
 static bool DownClick();
 static int ffstv();
 static bool Movie_Two_Hover(sf::Mouse mouse, sf::RenderWindow &window, sfe::Movie &movie2);
 static void SetLimits(float LX, float LY);
 static bool Is_Mouse_Within_Window(sf::RenderWindow &window, sf::Mouse &mouse);
 static bool Mouse_Wheel_Moved();
 static int stoint(const std::string s);
};

