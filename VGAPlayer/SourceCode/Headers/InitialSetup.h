#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class InitialSetup
{
private:

public:
	InitialSetup();
	~InitialSetup();
	std::string ffs;
	std::string mov;
	void movieWindow();
	void UI();
	void files();
	void openFile(int n);
	void LoadMovie(int n);
};

