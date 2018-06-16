#include "Animation.h"

using namespace std;

const double Animation::PI = 3.14159265;

sf::Uint8 Animation::Lerp_Opacity(sf::Uint8 value, const sf::Uint8 speed) {
 if (value != 0 && speed < value) {
  value -= (speed + 1);
  return value;
 }
 else if (value < speed) {
  return 0;
 }
 return 0;
}

sf::Uint8 Animation::Lerp_Opacity_Inverted(sf::Uint8 value, const sf::Uint8 speed) {
 if (value != 0 && speed < value) {
  value += (speed + 1);
  return value;
 }
 else if (value < speed) {
  return 0;
 }
 return 0;
}


sf::Uint8 Animation::Lerp_Value(sf::Uint8 start_Point, sf::Uint8 end_Point, const sf::Uint8 speed) {
 if (start_Point != end_Point && start_Point - end_Point > speed || end_Point - start_Point > speed) {
  if (start_Point < end_Point)
   start_Point += (speed + 1);
  else
   start_Point -= (speed + 1);

  //print.Log_Info("LERP_VALUE: startpoint = %i", static_cast<int>(start_Point));
  return start_Point;
 }
 else {
  return end_Point;
 }
}


sf::Uint8 Animation::Lerp_Cosine(sf::Uint8 start_Point, sf::Uint8 end_Point, const sf::Uint8 speed, int &test, bool &done) {
 if (test <= end_Point - 4) {
  done = false;
  test += speed;
  return static_cast<int>(sin((float)test * PI / (float)end_Point) * (float)end_Point);
 }
 else {
  done = true;
  return 0;
 }
}


float Animation::Lerp_float(float start_Point, float end_Point, float speed) {
 if (start_Point != end_Point && start_Point - end_Point > speed || end_Point - start_Point > speed) {
  if (start_Point < end_Point) {
   start_Point += speed;
  }
  else {
   start_Point -= speed;
  }
  return start_Point;
 }
 else {
  return end_Point;
 }
}

sf::Color Animation::Lerp_Color(sf::Color ref, sf::Color end_Point, const float speed, std::string colr) {
 ref.r = Animation::Lerp_Value(ref.r, end_Point.r, static_cast<sf::Uint8>(speed));
 ref.g = Animation::Lerp_Value(ref.g, end_Point.g, static_cast<sf::Uint8>(speed));
 ref.b = Animation::Lerp_Value(ref.b, end_Point.b, static_cast<sf::Uint8>(speed));
 return ref;
}

sf::Color Animation::Lerp_Color(sf::Color ref, sf::Color end_Point, const float speedR, const float speedG, const float speedB, std::string colr) {
 ref.r = Animation::Lerp_Value(ref.r, end_Point.r, static_cast<sf::Uint8>(speedR));
 ref.g = Animation::Lerp_Value(ref.g, end_Point.g, static_cast<sf::Uint8>(speedG));
 ref.b = Animation::Lerp_Value(ref.b, end_Point.b, static_cast<sf::Uint8>(speedB));
 return ref;
}

float Animation::Lerp_Position(float start_Point, float end_Point, const sf::Uint8 speed) {

 if (start_Point != end_Point && start_Point - end_Point > speed || end_Point - start_Point > speed) {
  if (start_Point < end_Point)
   start_Point += (speed + 1);
  else
   start_Point -= (speed + 1);
  return start_Point;
 }
 else {
  return end_Point;
 }
}
