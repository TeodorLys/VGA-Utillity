#pragma once
#include <string>
#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics\Color.hpp>
#include "Buttons.h"
#include "Switch.h"

class InitialSetup
{
private:
	void ImportfromFile();
	void setText(sf::Text &t, std::string str, sf::Vector2f pos, unsigned int charSize, sf::Font &font);
	sf::Image image;
protected:
	void setButtons(Buttons &b, float sX, float sY, std::string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY, float extra);
	void setSwitches(Switch &s, float size, sf::Vector2f pos);
public:
	size_t combHash;
	std::vector<size_t> allHash;
	InitialSetup();
	std::string ffs;
	std::string mov;
	void movieWindow();
	void UI();
	void files();
	void openFile(int n);
	void LoadMovie(int n);
	void menuButtonsSettings();
	void Movie2Limits();
	void moviePreset(std::string buff, float fbuff, std::string file);
	void CheckMovieWatched();
	void loadPreset(std::string buff, float fbuff);
	void rollBackPreset();
	void unloadPreset();
	void hashMovies();
};

