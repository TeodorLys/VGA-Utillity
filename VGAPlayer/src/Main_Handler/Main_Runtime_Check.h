#pragma once
class movBase;
class movieDuration;
class Play_Pause_Icon;
class Resized;

class Main_Runtime_Check
{
public:
 static bool border;

private:
 static int initx;
 static int inity;
 static int mx;
 static int my;
 static bool border_Infinity_Stopper;
 static bool moving_Second_Movie;
 static bool beforeStart;
public:
 static void Thread_Pause(std::mutex *m, bool *pause);
 static void When_Movie_is_Playing(movBase *movie, movieDuration &md, std::condition_variable *cv, std::mutex *m, bool *pause, bool *moving_Second_window);
 static void Play_Pause_Active_Icon(Play_Pause_Icon *play);
 static void Popout_Window_PollEvent(Resized &re);

};

