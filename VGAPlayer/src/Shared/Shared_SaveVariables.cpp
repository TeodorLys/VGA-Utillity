#include "Shared_SaveVariables.h"
#include "Save\Save_Able_Variables\SaveAble.h"

namespace Shared_Save {
 SaveSettings settings;
 SaveSettings saveMovies;
 SAInt        volume1("volume1", 0);
 SAInt        volume2("volume2", 0);
 SAInt        window_Width("window_Width", 0);
 SAInt        window_Height("window_Width", 0);
 SAFloat      mov1Time("mov1Time", 0);
 SAFloat      mov2Time("mov2Time", 0);
 SAFloat      mov2Offset("mov2Offset", 0);
 SAString     mov1Path("mov1Path", "\\");
 SAString     mov2Path("mov2Path", "\\");
 SABool       One_Switch_On("one_Switch", false);
 SABool	      maximized_On_Exit("maximized_On_Exit", false);
};