#pragma once
#include <string>
#include <fstream>
#include <boost\filesystem\path.hpp>

namespace Shared_Str {
 extern std::string moviePath;
 extern std::string APTpath;
 extern std::string strTime;
 extern std::string smallstrTime;
 extern std::string movieSavePath;
 extern std::string executing_Path;

 extern std::fstream setting;
 extern std::fstream movieFile;

 extern boost::filesystem::path current;
};