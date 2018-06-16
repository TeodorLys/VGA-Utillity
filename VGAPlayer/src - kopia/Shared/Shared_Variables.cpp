#include "Shared_Variables.h"

namespace Shared_Var {
 /*---(First Movie Timer)---*/
 unsigned int hour;
 unsigned int minute;
 unsigned int second;
 /*---(Second Movie Timer)---*/
 unsigned int smallhour;
 unsigned int smallminute;
 unsigned int smallsecond;

 float mov1SaveTime   = 0;
 float mov2SaveTime   = 0;
 float mov2OffsetTime = 0;
 float inc			  = 0;
 float secondInc      = 0;
 float w              = 0;
 float h              = 0;

 int mov1Vol = 0;   //fullscreen movie volume variable
 int mov2Vol = 0;   //Smaller movie volume variable
 
 //Temporary!!
 int getI   = 5;
 float getf = 0.01f;
};
