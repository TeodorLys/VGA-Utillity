#pragma once

#include <SFML\Window\Event.hpp>
#include <SFML\System\Time.hpp>

class Events;
class movBase;
class Debugging;
class keyPress
{
private:
 Events* ev;
 movBase** movie;
 Debugging *debug;
 sf::Time time;
public:
 keyPress(Events*, movBase**, Debugging*);
 void press(sf::Event event);
 inline void syncMovie();
};

