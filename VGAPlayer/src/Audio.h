#pragma once
class InitialSetup;

namespace sfe {
 class Movie;
};

class Audio{
private:
 InitialSetup *initial;
 const int Audio_Off = 5;
public:
 Audio(InitialSetup *initial_Object);
 float second_Mov_Vol = 0;
 int first_Mov_Vol = 0;
 void set_Volume_at_Runtime();
 void Initialize_First_Movie_Timer(sfe::Movie &Movie_One, size_t &Hour, size_t &Minute, size_t &Second);
 void Initialize_Second_Movie_Timer(sfe::Movie &Movie_Two, size_t &Small_Hour, size_t &Small_Minute, size_t &Small_Second);
};

