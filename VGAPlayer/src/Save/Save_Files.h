#pragma 
#include <vector>

class Audio;
class InitialSetup;

class Save_Files {
private:
public:
 static void Get_Saved_Files(Audio* _audio, InitialSetup *initial);
 static size_t Hash_Movies(std::vector<size_t> &HashRef, std::string ffstv_Path, std::string movie_Path);
 static void Load_Variables(std::string buff, float fbuff, std::string file);
 static void Set_Loaded_Variables(std::string buff, float fbuff);
 static void Check_Movie_Watched(std::vector<size_t> &Hash_Ref, size_t Combined_Hash);

 static void Variables_Settings_to_Save();
 static void Variables_Settings_to_Load();
 
 static void Variables_Movie_to_Save();
 static void Variables_Movie_to_Load();
};