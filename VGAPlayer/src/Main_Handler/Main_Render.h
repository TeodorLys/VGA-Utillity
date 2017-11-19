#pragma once
class Context_Handler;
class Debugging;
class Play_Pause_Icon;
class movBase;

class Main_Render
{
public:
 static void Local_Menu_Render(Context_Handler &context_Handle, Debugging &debug);
 static void Local_Movie_Render(Play_Pause_Icon *play, movBase *movie, Context_Handler *context_Handle, Debugging &debug);
};

