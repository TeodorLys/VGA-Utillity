#include "Shared_String.h"
#include <string>
#include <fstream>
#include <boost\filesystem\path.hpp>

namespace Shared_Str {
 std::string moviePath;
 std::string APTpath;
 std::string strTime;
 std::string smallstrTime;
 std::string movieSavePath;
 std::string executing_Path;

 std::fstream setting;
 std::fstream movieFile;

 boost::filesystem::path current;
};