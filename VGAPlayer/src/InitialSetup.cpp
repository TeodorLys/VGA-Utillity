#include <boost\filesystem\operations.hpp>
#include <sfeMovie\Movie.hpp>
#include "Handlers\Zip_File_Handler.h"
#include "Events\Actions.h"
#include "Events\Debugging.h"
#include "Objects\ContextMenuObjects.h"
#include "Objects\Spacer.h"
#include "Audio.h"
#include "Objects\Buttons.h"
#include "Objects\Switch.h"
#include "Objects\ContextMenu.h"
#include "Handlers\Context_Handler.h"
#include "Save\Save_Files.h"
#include "InitialSetup.h"
#include "Turbo.h"
#include "Objects\Debug_Variable.h"

/*---(Shared Variables)---*/
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_sfe_Movie.h"
#include "Shared\Shared_Variables.h"
#include "Shared\Shared_String.h"
#include "Shared\Shared_SaveVariables.h"
#include "Shared\Shared_Modules.h"
/*---(Shared Variables)---*/

using namespace std;

//Aspect ratio is weird... if second movie is 
//greater than two it is one value and otherwise it is another...
bool Check_Movie_Limits() {
 if (Shared_sfe::movie2->getSize().x / Shared_sfe::movie2->getSize().y > 2) {
  Actions::SetLimits(960 / (1920.f / Shared_sf::window.getSize().x), 455 / (1080.f / Shared_sf::window.getSize().y));
  return true;
 }
 else if (Shared_sfe::movie2->getSize().x / Shared_sfe::movie2->getSize().y < 2) {
  Actions::SetLimits(930 / (1920.f / Shared_sf::window.getSize().x), 510 / (1080.f / Shared_sf::window.getSize().y));
  return false;
 }
 return false;
}


InitialSetup::InitialSetup(mouseEvent* mou, Audio *Audio_Object, Context_Handler* cM_Handle, Resized *resized_Object) :
 ffs("NONE"), mov("NONE"), me(mou), _audio(Audio_Object), context_Handle(cM_Handle), re(resized_Object) {}


void InitialSetup::Setup_Window() {
 turbo t;
 sf::Image icon;

 sf::ContextSettings settings;

 settings.antialiasingLevel = 0;

 sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

 //Sets default window size if saved size was not loaded
 if (Shared_Var::w == 0 && Shared_Var::h == 0) {
  Shared_Var::w = static_cast<float>(desktopMode.width);   //Get main monitor width
  Shared_Var::h = static_cast<float>(desktopMode.height);   //Get main monitor height
 }

 print.Log_Info("Display resolution, x: %i y: %i", (int)Shared_Var::w, (int)Shared_Var::h);

 Shared_sf::window.create(sf::VideoMode((int)Shared_Var::w, (int)Shared_Var::h), "VGAPlayer", sf::Style::Default, settings);   //Creates the actual window
 Shared_sf::window.setFramerateLimit(60);   //Framerate limit
 Shared_sf::window.setVerticalSyncEnabled(true);   //Since this is something moving, why not add some vSync

 Import_from_File();
 
 //Need to have these 'setSize' here to "Reset" the window dimentions... its Weird
 Shared_sf::window.setSize(sf::Vector2u(Shared_sf::window.getSize().x - 10, Shared_sf::window.getSize().y));
 if (Shared_bool::maximized_On_Exit_Program)
  ShowWindow(Shared_sf::window.getSystemHandle(), SW_MAXIMIZE);

 Shared_sf::window.setSize(sf::Vector2u(Shared_sf::window.getSize().x + 10, Shared_sf::window.getSize().y));

 icon.create(32, 32, t.turboBuddy);   //Window icon

 Shared_sf::window.setIcon(32, 32, icon.getPixelsPtr());
 print.Log_Info("Created the window icon");

 //
 //The Menu Background
 //

 Shared_sf::theCrew.setSize(sf::Vector2f((float)Shared_sf::theCrew_Texture.getSize().x, (float)Shared_sf::theCrew_Texture.getSize().y));
 Shared_sf::theCrew.setOrigin((float)Shared_sf::theCrew.getSize().x / 2, (float)Shared_sf::theCrew.getSize().y / 2);
 Shared_sf::theCrew.setPosition((float)Shared_sf::window.getSize().x / 2, 300);

 //"Fullscreen" movie Volume
 setText(Shared_sf::vol1, to_string(_audio->first_Mov_Vol), sf::Vector2f(0, 0), 32, Shared_sf::font);
 //"Fullscreen" movie timer
 setText(Shared_sf::tTimer, "0", sf::Vector2f(0, Shared_sf::window.getSize().y - Shared_sf::tTimer.getGlobalBounds().height), 32, Shared_sf::font);
 //"Smaller" movie Volume
 setText(Shared_sf::vol2, to_string((int)_audio->second_Mov_Vol), sf::Vector2f((float)Shared_sf::window.getSize().x, 0), 32, Shared_sf::font);
 //"Smaller" movie timer
 setText(Shared_sf::smalltTimer, "0", sf::Vector2f((float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y), 32, Shared_sf::font);
 

 Shared_sf::b.setTexture(&Shared_sf::base);
 Shared_sf::b.setSize(sf::Vector2f((float)Shared_sf::window.getSize().x, (float)Shared_sf::window.getSize().y));

 context_Handle->Menu_Object_Setup();
}

template<class T>
void Add_to_Debugger(std::string s, Debug_Variable &dv, Debugging &d, T &var) {
 dv.make_Debuggable(s);
 dv.init_Data<T>(var);
 dv.set_ID(typeid(var).name());
 d.Add_Debug_Variables(dv);
}

void InitialSetup::init_Debug(Debugging &debug) {
 Debug_Variable dv;
 
 Add_to_Debugger<float>("NOT IN USE!!!aa", dv, debug, Shared_Var::getf);

 debug.Setup();
}

 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Imports all images and textures
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::Import_from_File() {
 string theCrew_Path;
 string t = boost::filesystem::temp_directory_path().string();   //Gets the drive letter of where windows is installed
 t.erase(1, t.length());
 string safe_Font_Path = t + ":\\windows\\fonts\\arial.ttf";   //If vgafont is not found
 string sys_Font_Path = t + ":\\windows\\fonts\\segoeui.ttf";   //For all system stuff, context menu etc...
 Zip_File_Handler images;  //Returns the images that is in the content zip file

 //Generates a random number, to deside which image to present
 switch (Actions::ffstv()) {
 case 0:
  theCrew_Path = "FFSTV.PNG";
  break;

 case 1:
  theCrew_Path = "FFSTVMario.PNG";
  break;

 case 2:
  theCrew_Path = "FFSTVps.PNG";
  break;

 default:
  theCrew_Path = "FFSTV.PNG";
  break;
 }

 print.Log_Info("Generated Crew, %s", theCrew_Path.c_str());

 string zip = Shared_Str::executing_Path + "\\thecrew.zip";

 images.Open_Zip(zip.c_str());
 images.Find_File(theCrew_Path.c_str());

 if (!Shared_sf::theCrew_Texture.loadFromMemory(images.Get_File_Info().content, images.Get_File_Info().size)) {
  print.Log_Error("%s was invalid or corrupted", theCrew_Path.c_str());
  msg = MessageBox(NULL, L"Could not load image.\nSomething has been deleted", L"IMAGE NOT LOADED", MB_OKCANCEL);
  if (msg == IDOK || msg == IDCANCEL)
   exit(-1);
 }
 else {
  print.Log_Success("Successfully loaded theCrew");
  Shared_sf::theCrew.setTexture(&Shared_sf::theCrew_Texture);
 }

 //
 //Load Base Background
 //

 string BaseTemp = Shared_Str::executing_Path + "\\base.png";

 images.Find_File("Base.PNG");

 if (!Shared_sf::base.loadFromMemory(images.cn.content, images.cn.size)) {
  print.Log_Error("%s could not be opened", BaseTemp);
  msg = MessageBox(NULL, L"COULD NOT LOAD IMAGE", L"INVALID FILE PATH", MB_RETRYCANCEL);
 }
 else {
  print.Log_Success("Successfully loaded Background");
 }

 //Tries to load the SEGOEUI font
 if (!Shared_sf::sysFont.loadFromFile(sys_Font_Path)) {
  print.Log_Error("%s was invalid or corrupted", sys_Font_Path);
  msg = MessageBox(NULL, L"Could not load System Font", L"PATH NOT FOUND", MB_OKCANCEL);
  if (msg == IDCANCEL || msg == IDOK)  //What the user clicks on the MessageBox
   exit(-1);
 }
 else {
  print.Log_Success("Successfully loaded 'System Font'");
 }
 string VGAFont = Shared_Str::executing_Path + "\\VGAFont.ttf";

 //Tries to load the VGAfont
retry:
 if (!Shared_sf::font.loadFromFile(VGAFont)) {
  print.Log_Warning("%s was not found, Loading Backup font...", VGAFont);
  if (!Shared_sf::font.loadFromFile(safe_Font_Path)) {
   print.Log_Error("'Backup Font' failed to load");
   msg = MessageBox(NULL, L"DEFAULT FONT COULD NOT BE LOADED", L"FONT NOT LOADED", MB_RETRYCANCEL);
   switch (msg) {
   case IDCANCEL:
	exit(-1);
   case IDRETRY:
	goto retry;
   }
  }
  else {
   print.Log_Success("Successfully loaded 'Backup Font'");
  }
 }
 else {
  print.Log_Success("Successfully loaded 'VGAFont'");
 }
}//Import from file Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Creates an open file prompt
 ///////////////////////////////////////////////////////////////////////////////////////////
bool InitialSetup::OpenFile(int n) {
 OPENFILENAMEA file;
 string s;
 char c[256];
 HANDLE h;
 HWND hwnd = NULL;
 ZeroMemory(&file, sizeof(file));
 file.lStructSize = sizeof(file);
 file.hwndOwner = Shared_sf::window.getSystemHandle();
 file.lpstrFile = c;
 file.lpstrFile[0] = '\0';
 file.nMaxFile = sizeof(c);
 file.nFilterIndex = 1;
 file.lpstrFileTitle = NULL;
 file.nMaxFileTitle = 0;
 file.lpstrInitialDir = NULL;
 file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

 if (GetOpenFileNameA(&file) == TRUE) {
  h = CreateFileA(file.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, 
				  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
  CloseHandle(h);
  c != "" ? s = c : 0;
  n == 1 ? ffs = s : mov = s;
  return true;
 }
 print.Log_Warning("'OpenFile' was closed without a given path");
 return false;
}//Open file Function END


///////////////////////////////////////////////////////////////////////////////////////////
/// \Loads the movies into memory
///////////////////////////////////////////////////////////////////////////////////////////
bool InitialSetup::LoadMovie(int n, sfe::Movie **Movie_to_Load) {
 if (!OpenFile(n)) {
  return false;
 }
 //So it doesnt try to load a file that has not been selected, i.e "NONE" is defalt (which is not a path...)
 if (ffs != "NONE" || mov != "NONE") {
  string h;
  string movie_Path;

  if (n == 1)
   movie_Path = ffs;
  else
   movie_Path = mov;
  
  delete *Movie_to_Load;
  *Movie_to_Load = new sfe::Movie;
  if (!(**Movie_to_Load).openFromFile(movie_Path)) {
   print.Log_Warning("%s could not be opened", movie_Path.c_str());
   h = "Could not open\n" + movie_Path;
   msg = MessageBox(NULL, (LPCWSTR)h.c_str(), L"PATH WAS NOT FOUND", MB_OKCANCEL);
   if (msg == IDOK || msg == IDCANCEL)
	goto Failed;
  }
  else {
   print.Log_Success("Successfully loaded %s", movie_Path.c_str());
   print.Log_Info("Audio Channels: %i", (**Movie_to_Load).getChannelCount());
   print.Log_Info("Duration: %i", (int)(**Movie_to_Load).getDuration().asSeconds());
   print.Log_Info("Framerate: %i", (int)(**Movie_to_Load).getFramerate());
   print.Log_Info("Sample rate: %ihz", (**Movie_to_Load).getSampleRate());

   if (n == 1)
	(**Movie_to_Load).setVolume(static_cast<float>(Shared_Var::mov1Vol));
   else
	(**Movie_to_Load).setVolume(static_cast<float>(Shared_Var::mov2Vol));

   print.Log_Info("Volume: %i", (int)(**Movie_to_Load).getVolume());

   Shared_Mod::ffstv->outLine = sf::Color(20, 255, 20);
   Shared_Mod::ffstv->setButtonColor(5.5f);
   if (n == 2) {
	movie_Two_is_Greater = Check_Movie_Limits();
	goto Success;
   }
   return true;
  }
  Failed:
  return false;
 }

 Success:
 if (ffs != "NONE" && mov != "NONE") {
  print.Log_Success("Successfully loaded both movies");
  combHash = Save_Files::Hash_Movies(allHash, ffs, mov);
  Save_Files::Check_Movie_Watched(allHash, combHash);
  return true;
 }
 //Last resort - fail message
 print.Log_Error("Some if statement fell through...");
 return false;
}//LoadMovie Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Sets all settings for text objects
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::setText(sf::Text &t, string str, sf::Vector2f pos, unsigned int charSize, sf::Font &font) {
	t.setString(str);
	t.setCharacterSize(charSize);
	t.setScale(1, 1);
	t.setFillColor(sf::Color(255, 255, 255));
	t.setFont(font);
	t.setStyle(sf::Text::Regular);
	t.setPosition(pos);
}//SetText Function END


 ///////////////////////////////////////////////////////////////////////////////////////////
 /// \Initializes all of the menu buttons an switches									 ///
 ///////////////////////////////////////////////////////////////////////////////////////////
void InitialSetup::menuButtonsSettings() {
 //Sets the PLAY Button settings
 setButtons(*Shared_Mod::play, 20, 20, "PLAY", sf::Color(50, 50, 50),
			sf::Color(100, 65, 0), 5.5f, sf::Color(100, 65, 0),
			sf::Vector2f(Shared_sf::window.getSize().x / 2.f, Shared_sf::window.getSize().y - 100.f),
			(Shared_sf::window.getSize().x / width) * 2,(Shared_sf::window.getSize().y / height) * 2, 7);

 //Sets the OPEN FFSTV VIDEO settings
 setButtons(*Shared_Mod::ffstv, 20, 20, "LOAD FFSTV VIDEO", sf::Color(0, 0, 0),
			sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
			sf::Vector2f(200.f, Shared_sf::window.getSize().y - 100.f),
			Shared_sf::window.getSize().x / width, Shared_sf::window.getSize().y / height, 5);

 //Sets the OPEN MOVIE FILE settings
 setButtons(*Shared_Mod::film, 20, 20, "LOAD MOVIE FILE", sf::Color(0, 0, 0),
			sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
			sf::Vector2f(Shared_sf::window.getSize().x - 200.f, Shared_sf::window.getSize().y - 100.f),
			Shared_sf::window.getSize().x / width, Shared_sf::window.getSize().y / height, 5);

 setButtons(*Shared_Mod::replay, 20, 20, "Replay", sf::Color(50, 50, 50, 0),
			sf::Color(255, 125, 0, 0), 5.5f, sf::Color(255, 125, 0),
			sf::Vector2f((float)Shared_sf::window.getSize().x / 2 + (Shared_sf::window.getSize().x / 8),
			(float)Shared_sf::window.getSize().y / 2), Shared_sf::window.getSize().x / width, Shared_sf::window.getSize().y / height, 5);

 setButtons(*Shared_Mod::ret, 15, 15, "Return", sf::Color(50, 50, 50, 0),
			sf::Color(255, 125, 0, 0), 5.5f, sf::Color(255, 125, 0),
			sf::Vector2f((float)Shared_sf::window.getSize().x / 2 - (Shared_sf::window.getSize().x / 8),
			(float)Shared_sf::window.getSize().y / 2), Shared_sf::window.getSize().x / width, Shared_sf::window.getSize().y / height, 5);

 setButtons(*Shared_Mod::secondReplay, 20, 20, "LOAD NEW FILM", sf::Color(0, 0, 0),
			sf::Color(255, 125, 0), 5.5f, sf::Color(255, 125, 0),
			sf::Vector2f(200.f, Shared_sf::window.getSize().y - 100.f), Shared_sf::window.getSize().x / width,
			Shared_sf::window.getSize().y / height, 5);

 setSwitches(*Shared_Mod::oneMovie, 5, sf::Vector2f(Shared_Mod::play->getPosition().x, Shared_Mod::play->getPosition().y - Shared_Mod::play->getSize().y));
}


//Sets the initial Buttons variables
void InitialSetup::setButtons(Buttons &b, float sX, float sY, string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY, float extra) {
 b.setSize(sX, sY);
 b.setText(text);
 b.setScale(sf::Vector2f(scaleX, scaleY));
 b.baseColor = sf::Color(c);
 b.outLine   = sf::Color(out);
 b.setButtonColor(outsize);
 b.setTextColor(tc);
 b.setPosition(p, extra);
 b.baseColor = sf::Color(c);
 b.outLine   = sf::Color(out);
}


void InitialSetup::setSwitches(Switch &s, float size, sf::Vector2f pos) {
 s.setBase();
 s.setScale(sf::Vector2f(size, size));
 s.setPosition(sf::Vector2f(pos));
}


void InitialSetup::Movie2Limits() {
	movie_Two_is_Greater ? 
	 Actions::SetLimits(960 / (1920.f / Shared_sf::window.getSize().x), 455 / (1080.f / Shared_sf::window.getSize().y)) :
	 Actions::SetLimits(930 / (1920.f / Shared_sf::window.getSize().x), 510 / (1080.f / Shared_sf::window.getSize().y));
}


void InitialSetup::initializeButtons() {
 Shared_Mod::play  = new Buttons(&Shared_sf::window, &Shared_sf::mouse, &Shared_sf::font, &Shared_bool::focus);
 Shared_Mod::ffstv = new Buttons(&Shared_sf::window, &Shared_sf::mouse, &Shared_sf::font, &Shared_bool::focus);
 Shared_Mod::film  = new Buttons(&Shared_sf::window, &Shared_sf::mouse, &Shared_sf::font, &Shared_bool::focus);

 Shared_Mod::replay       = new Buttons(&Shared_sf::window, &Shared_sf::mouse, &Shared_sf::font, &Shared_bool::focus);
 Shared_Mod::ret          = new Buttons(&Shared_sf::window, &Shared_sf::mouse, &Shared_sf::font, &Shared_bool::focus);
 Shared_Mod::secondReplay = new Buttons(&Shared_sf::window, &Shared_sf::mouse, &Shared_sf::font, &Shared_bool::focus);

 Shared_Mod::oneMovie = new Switch(Shared_bool::focus, Shared_sf::mouse, Shared_sf::window);
 
 Shared_Mod::about       = new textButton;
 Shared_Mod::mainMovText = new textButton;
 Shared_Mod::spacers     = new Spacer;
}
