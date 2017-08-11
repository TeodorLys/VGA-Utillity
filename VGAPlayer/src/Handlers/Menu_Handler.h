#pragma once
class InitialSetup;
class movBase;
class Audio;
class Events;

namespace sfe {
 class Movie;
};

class Menu_Handler {
private:
 bool can_Play = false;
 void Empty_Path(InitialSetup &initial);
public:
 Menu_Handler();
 void Menu_Buttons(sfe::Movie &Movie_One, sfe::Movie &Movie_Two,
				   InitialSetup &initial, Audio &_audio, Events &Events_Object);
 void End_Screen(bool &get_Doonce, sfe::Movie &Movie_One, InitialSetup &initial, movBase &Movie_Object);
 static void Return_To_Menu(movBase &Movie_Events_Object);
 static void Replay_Movies(sfe::Movie &Movie_One, movBase &Movie_Events_Object);
};

 