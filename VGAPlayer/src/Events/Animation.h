#pragma once

#include <SFML\Graphics\Color.hpp>
#include "../Logger.h"
#include <algorithm>

class Animation {
private:
 static const double PI;
public:
 static sf::Uint8 Lerp_Opacity(sf::Uint8 value, const sf::Uint8 speed);
 static sf::Uint8 Lerp_Opacity_Inverted(sf::Uint8 value, const sf::Uint8 speed);
 static sf::Uint8 Lerp_Value(sf::Uint8 start_Point, sf::Uint8 end_Point, const sf::Uint8 speed);
 static sf::Uint8 Lerp_Cosine(sf::Uint8 start_Point, sf::Uint8 end_Point, const sf::Uint8 speed, int &test, bool &done);
 static sf::Color Lerp_Color(sf::Color ref, sf::Color end_Point, const float speed, std::string colr);
 static sf::Color Lerp_Color(sf::Color ref, sf::Color end_Point, const float speedR, const float speedG, const float speedB, std::string colr);
 static float Lerp_float(float start_Point, float end_Point, float speed);
 static float Lerp_Position(float start_Point, float end_Point, const sf::Uint8 speed);
};

