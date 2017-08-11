#include "Zip_File_Handler.h"
#include "../Logger.h"
#include <zip.h>


using namespace std;

Zip_File_Handler::Zip_File_Handler(){
}

Zip_File_Handler::~Zip_File_Handler() {
 delete[] cn.content;
}

bool Zip_File_Handler::Open_Zip(const char* path) {
 z = zip_open(path, 0, &error);
 if (error > 0) {
  print.Log_Error("Zip file could not be opened, Error code: %i", error);
  return false;
 }
 else {
  print.Log_Success("Zip file %s opened", path);
  is_Open = true;
  return true;
 }
}

bool Zip_File_Handler::Find_File(const char* file_Name) {
 if (is_Open) {
  zip_stat_init(&st);
  if (zip_stat(z, file_Name, 0, &st) < 0) {
   print.Log_Error("File cound not be found...");
   return false;
  }
  else {
   cn.content = new char[static_cast<int>(st.size)];
   cn.size = static_cast<int>(st.size);
   f = zip_fopen(z, file_Name, 0);
   zip_fread(f, cn.content, st.size);
   zip_fclose(f);
   print.Log_Success("%s was found", file_Name);
   return true;
  }
 }
 else {
  print.Log_Warning("Zip file has not been opened");
  return false;
 }
}

Zip_File_Handler::content_Info Zip_File_Handler::Get_File_Info() {
 return cn;
}