#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class InitialSetup
{
private:
	void ImportfromFile();
	void setText(sf::Text &t, std::string str, sf::Vector2f pos);
	sf::Image image;
public:
	InitialSetup();
	std::string ffs;
	std::string mov;
	void movieWindow();
	void UI();
	void files();
	void openFile(int n);
	void LoadMovie(int n);
};

