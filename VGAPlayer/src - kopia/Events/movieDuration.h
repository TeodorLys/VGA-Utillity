#pragma once

class InitialSetup;

class movieDuration
{
private:
 unsigned int currentHour;
 unsigned int currentMinute;
 unsigned int currentSecond;
 unsigned int smallcurrentHour;
 unsigned int smallcurrentMinute;
 unsigned int smallcurrentSecond;
 InitialSetup* initial;
public:
 movieDuration(InitialSetup*);
 void Timer();
 void smallTimer();
};

