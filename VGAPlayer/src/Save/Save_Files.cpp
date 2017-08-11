#include "Save_Files.h"
#include "../DEBUG_Defines.h"
#include "../Logger.h"
#include "../Objects/Switch.h"
#include "../InitialSetup.h"
#include <string>
#include "../Shared/Shared_String.h"
#include <boost\filesystem\operations.hpp>
#include "../Shared/Shared_SaveVariables.h"
#include "../Shared/Shared_Variables.h"
#include "../Shared/Shared_Boolean.h"
#include "../Shared/Shared_Modules.h"
#include "../Audio.h"

using namespace std;

//Opens the Settings fstream, and loads it into Settings Object.
void Save_Files::Get_Saved_Files(Audio* _audio, InitialSetup *initial) {
 
 //Sets this because the "Openfile" function
 //will change the "Current path" to the Opened file path
 Shared_Str::current = Shared_Str::executing_Path;

 string config_Path = Shared_Str::current.string() + "\\config/Settings.ini";

 if (boost::filesystem::exists(config_Path)) {
  Shared_Str::setting.open(config_Path, fstream::in);

  if (Shared_Str::setting.is_open()) {
   Variables_Settings_to_Load();
   Shared_Save::settings.Load_Settings(Shared_Str::setting);

   _audio->first_Mov_Vol = Shared_Save::volume1.getV(0); //parameter does nothing... god damn polymorphism
   _audio->second_Mov_Vol = static_cast<float>(Shared_Save::volume2.getV(0));  
   Shared_Var::w = static_cast<float>(Shared_Save::window_Width.getV(0));
   Shared_Var::h = static_cast<float>(Shared_Save::window_Height.getV(0));
   print.Log_Info("Loaded Switch %i", static_cast<int>(Shared_Save::One_Switch_On.getV(false)));
   Shared_Mod::oneMovie->switchON = Shared_Save::One_Switch_On.getV(false);
   Shared_bool::maximized_On_Exit_Program = Shared_Save::maximized_On_Exit.getV(false);

   Logger::log().Log_Info("First Movie: %i Second Movie: %i", _audio->first_Mov_Vol, static_cast<int>(_audio->second_Mov_Vol));

  }
  Shared_Str::setting.close();
 }
 //Creates the settings file, if it doesnt exist.
 else {
  Shared_Str::setting.open(config_Path, fstream::out);
  Variables_Settings_to_Save();
  Shared_Str::setting.close();
 }
 //Create the directory if it doesnt exitst.
 boost::filesystem::path p(Shared_Str::current.string() + "\\config");
 !boost::filesystem::exists(p) ? boost::filesystem::create_directory(p) : 0;

}//Files Function END


// This will be static since it doesnt use any local variables
size_t Save_Files::Hash_Movies(vector<size_t> &HashRef, string ffstv_Path, string movie_Path) {
 fstream fhash;

 string buff = Shared_Str::current.string() + "\\config\\hash.vga";

 if (!boost::filesystem::exists(buff)) {
  fhash.open(buff, fstream::out);
  fhash.close();
 }
 else {
  fhash.open(buff, fstream::in);
  for (string s; getline(fhash, s);) {
   HashRef.push_back(atoi(s.c_str()));
  }
  fhash.close();
 }

 size_t ffsHash = hash<string>{}(ffstv_Path);
 size_t movHash = hash<string>{}(movie_Path);

 return(ffsHash + movHash);
}


/*--(Private Inlined functions for Load_Variables)--*/
 inline void File_Exists__Load_Var(std::string &file) {
  Shared_Str::movieFile.open(file, fstream::in);
  if (Shared_Str::movieFile.is_open()) {
   //
   //Will be exchanged, by function
   //
   Save_Files::Variables_Movie_to_Load();
   Shared_Save::saveMovies.Load_Settings(Shared_Str::movieFile);
  }
  else {
   Logger::log().Log_Warning("Fstream could not be opened on %s", file);
  }

  Shared_Str::movieFile.close();
 }

 inline void File_Does_Not_Exists_PreSave(std::string &file) {
  Shared_Str::movieFile.open(file, fstream::out);
  if (Shared_Str::movieFile.is_open()) {
   //
   //Will be exchanged, by function
   //
   Save_Files::Variables_Movie_to_Save();
  }
  else {
   Logger::log().Log_Warning("Fstream could not be opened on %s", file);
  }
  Shared_Str::movieFile.close();
 }
/*--(Private Inlined functions for Load_Variables)--*/

void Save_Files::Load_Variables(string buff, float fbuff, string file) {
 if (boost::filesystem::exists(file)) 
  File_Exists__Load_Var(file);
 else
  File_Does_Not_Exists_PreSave(file);

 Shared_Str::movieFile.close();
}


void Save_Files::Check_Movie_Watched(std::vector<size_t> &Hash_Ref, size_t Combined_Hash) {
 string buff;
 string file  = Shared_Str::current.string() + "\\config\\movieSave0.ini";
 float fbuff  = 0;
 int index    = 0;

 for (unsigned int a = 0; a < Hash_Ref.size(); a++) {
  if (Hash_Ref[a] == Combined_Hash) {
   index = a;
   goto Success;
   break;
  }
 }
 file = Shared_Str::current.string() + "\\config\\movieSave" + to_string(Hash_Ref.size()) + ".ini";
 Shared_Str::movieSavePath = file;
 Hash_Ref.push_back(Combined_Hash);
 return;

Success:
 Logger::log().Log_Success("Success with %s", file);
 //Makes up a name for the movie save file... @DoesntWork!!
 file = Shared_Str::current.string() + "\\config\\movieSave" + to_string(index) + ".ini";
 
 Shared_Str::movieSavePath = file;
 Load_Variables(buff, fbuff, file);   //Loads variables into a vector
 Set_Loaded_Variables(buff, fbuff);   //Loads the saved variables into the correct SA Object
}


//Loads the variables into standard variables
void Save_Files::Set_Loaded_Variables(string buff, float fbuff) {
 Shared_Var::mov1SaveTime   = Shared_Save::mov1Time.getV(0.f);
 Shared_Var::mov2SaveTime   = Shared_Save::mov2Time.getV(0.f);
 Shared_Var::mov2OffsetTime = Shared_Save::mov2Offset.getV(0.f);
 Shared_Str::APTpath        = Shared_Save::mov1Path.getV('\0');
 Shared_Str::moviePath      = Shared_Save::mov2Path.getV('\0');
}


//Order Is important!!!
void Save_Files::Variables_Settings_to_Save() {
 Shared_Save::settings.saveVariable(Shared_Save::volume1, Shared_Str::setting);
 Shared_Save::settings.saveVariable(Shared_Save::volume2, Shared_Str::setting);
 Shared_Save::settings.saveVariable(Shared_Save::window_Width, Shared_Str::setting);
 Shared_Save::settings.saveVariable(Shared_Save::window_Height, Shared_Str::setting);
 Shared_Save::settings.saveVariable(Shared_Save::One_Switch_On, Shared_Str::setting);
 Shared_Save::settings.saveVariable(Shared_Save::maximized_On_Exit, Shared_Str::setting);
}


//Order Is important!!!
void Save_Files::Variables_Settings_to_Load() {
 Shared_Save::settings.Load(Shared_Save::volume1);
 Shared_Save::settings.Load(Shared_Save::volume2);
 Shared_Save::settings.Load(Shared_Save::window_Width);
 Shared_Save::settings.Load(Shared_Save::window_Height);
 Shared_Save::settings.Load(Shared_Save::One_Switch_On);
 Shared_Save::settings.Load(Shared_Save::maximized_On_Exit);
}


//Order Is important!!!
void Save_Files::Variables_Movie_to_Save() {
 Shared_Save::saveMovies.saveVariable(Shared_Save::mov1Time, Shared_Str::movieFile);
 Shared_Save::saveMovies.saveVariable(Shared_Save::mov2Time, Shared_Str::movieFile);
 Shared_Save::saveMovies.saveVariable(Shared_Save::mov2Offset, Shared_Str::movieFile);
 Shared_Save::saveMovies.saveVariable(Shared_Save::mov1Path, Shared_Str::movieFile);
 Shared_Save::saveMovies.saveVariable(Shared_Save::mov2Path, Shared_Str::movieFile);
}


//Order Is important!!!
void Save_Files::Variables_Movie_to_Load() {
 Shared_Save::saveMovies.Load(Shared_Save::mov1Time);
 Shared_Save::saveMovies.Load(Shared_Save::mov2Time);
 Shared_Save::saveMovies.Load(Shared_Save::mov2Offset);
 Shared_Save::saveMovies.Load(Shared_Save::mov1Path);
 Shared_Save::saveMovies.Load(Shared_Save::mov2Path);
}
