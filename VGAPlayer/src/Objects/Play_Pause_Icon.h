#pragma once

#include <SFML\Graphics\ConvexShape.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Texture.hpp>

class Play_Pause_Icon {
private:
 sf::ConvexShape playShape;
 sf::RectangleShape PauseShape[2];
 sf::CircleShape background;
 sf::Texture t1;
 sf::Texture t2;
public:
 bool is_Paused = false;
 Play_Pause_Icon();
 void setPosition(float, float);
 void setSize(float);
 void Draw();
 bool set_Paused(bool b);
 float getSize();
 sf::Color getColor();
 void setColor(sf::Color);
private:
 void Update_Rect_Position();
 void show_Paused();
 void setRectPosition(float, float);
};

