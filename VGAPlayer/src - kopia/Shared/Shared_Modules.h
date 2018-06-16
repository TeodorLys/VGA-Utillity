#pragma once
#include <vector>


class Buttons;
class Switch;
class textButton;
class ContextMenu;
class Spacer;

namespace Shared_Mod {
 extern Buttons *play;
 extern Buttons *ffstv;
 extern Buttons *film;
 extern Buttons *replay;  //End screen when the first is over
 extern Buttons *ret;	   //End screen stuff here too...
 extern Buttons *secondReplay;  //When the second movie is over

 extern Switch *oneMovie;

 extern textButton *about;
 extern textButton *mainMovText;

 extern ContextMenu allCM[2];

 #define basic allCM[0]
 #define mainMovie allCM[1]

 extern Spacer *spacers;
};