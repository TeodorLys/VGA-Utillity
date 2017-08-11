#include "Themes.h"
//#include "GlobalVariables.h"
//#include <fstream>
//#include <iostream>

using namespace std;

Themes::Themes(){
}


void Themes::setup() {
	//ifstream file;
	//int t = 0;

	//file.open("c:\\users\\teodo\\desktop\\testing.txt", fstream::binary);

	////getline(file, IconSTR);

	////cout << IconSTR << endl;

	////	if (!IconIMG.loadFromMemory(IconSTR.c_str(), 697)) {
	////		GV::value.msg = MessageBox(NULL, L"COULD NOT LOAD THEME", L"ICON PHOTO WAS CORRUPT", MB_OK);
	////	}
	////	if (GV::value.msg == IDOK)
	////		exit(-1);

	//for (string s; getline(file, s);) {
	//	//cout << s << endl;
	//	if (s.find("//") != string::npos)
	//		break;

	//	set.push_back(s);
	//}

	//for (unsigned int a = 0; a < set.size(); a++) {
	//	if (set[a].find("background") != string::npos) {
	//		if (set[a].find("true") != string::npos)
	//			bg = true;
	//		else if (set[a].find("false") != string::npos)
	//			bg = false;
	//	}
	//	else if (set[a].find("iconImg") != string::npos) {
	//		if (set[a].find("true") != string::npos)
	//			icon = true;
	//		else if (set[a].find("false") != string::npos)
	//			icon = false;
	//		t = a;
	//	}
	//}

	//if (set[t].find("c") != string::npos) {
	//	posX = GV::sfm.window.getSize().x / 2;
	//}
	//else if (set[t].find("ulc") != string::npos) {
	//	posX = 0;
	//}
	//else if (set[t].find("urc") != string::npos) {
	//	posX = GV::sfm.window.getSize().x;
	//}
	//else if (set[t].find("llc") != string::npos) {
	//	posX = 0;
	//}
	//else if (set[t].find("lrc") != string::npos) {
	//	posX = GV::sfm.window.getSize().x;
	//}

	//if (set[t + 1].find("c") != string::npos) {
	//	posY = GV::sfm.window.getSize().y / 2;
	//}
	//else if (set[t + 1].find("ulc") != string::npos) {
	//	posY = 0;
	//}
	//else if (set[t + 1].find("urc") != string::npos) {
	//	posY = 0;
	//}
	//else if (set[t + 1].find("llc") != string::npos) {
	//	posY = GV::sfm.window.getSize().y;
	//}
	//else if (set[t + 1].find("lrc") != string::npos) {
	//	posY = GV::sfm.window.getSize().y;
	//}

	//bool iend = false;

	//vector<char> buffer;

	//for (string s; getline(file, s);) {
	//	for (char c : s) {
	//		/*cout << s << endl;*/
	//		buffer.push_back(c);
	//	}
	//	if (s.find("IEND") != string::npos)
	//		iend = true;

	//	if (iend && s.find("//") != string::npos)
	//		break;
	//}

	//file.close();

	//if (!IconIMG.loadFromMemory(&buffer[0], IconSTR.size())) {
	//	GV::value.msg = MessageBox(NULL, L"COULD NOT LOAD THEME", L"ICON PHOTO WAS CORRUPT", MB_OK);
	//}
	//if (GV::value.msg == IDOK)
	//	exit(-1);

}