#include "Shared_Modules.h"
#include "Objects\Buttons.h"
#include "Objects\Switch.h"
#include "Objects\ContextMenuObjects.h"
#include "Objects\ContextMenu.h"
#include "Shared\Shared_sfml_Objects.h"



namespace Shared_Mod {
 Buttons *play;
 Buttons *ffstv;
 Buttons *film;
 Buttons *replay;  //End screen when the first is over
 Buttons *ret;	   //End screen stuff here too...
 Buttons *secondReplay;  //When the second movie is over

 Switch *oneMovie;

 textButton *about;
 textButton *mainMovText;

 Spacer *spacers;
};