#pragma once
#include "../Save/Save_Able_Variables/SaveAble.h"
#include "../Save/Save_Able_Variables/SaveSettings.h"

namespace Shared_Save {
 extern SaveSettings settings;
 extern SaveSettings saveMovies;
 extern SAInt        volume1;
 extern SAInt        volume2;
 extern SAInt        window_Width;
 extern SAInt        window_Height;
 extern SAFloat      mov1Time;
 extern SAFloat      mov2Time;
 extern SAFloat      mov2Offset;
 extern SAString     mov1Path;
 extern SAString     mov2Path;
 extern SABool       One_Switch_On;
 extern SABool       maximized_On_Exit;
};