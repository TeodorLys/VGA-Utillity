#pragma once
#include <SFML\Graphics\Text.hpp>
#include "Logger.h"
#include <memory>


class Buttons;
class Switch;
class mouseEvent;
class Buttons;
class Switch;
class textButton;
class ContextMenu;
class Spacer;
class Audio;
class Context_Handler;
class Resized;
class Debugging;

namespace sfe {
 class Movie;
};


class InitialSetup {
public:
 size_t combHash;
 std::vector<size_t> allHash;
 std::string ffs;
 std::string mov;
private:
 int msg = 0;
 void Import_from_File();
 void setText(sf::Text &t, std::string str, sf::Vector2f pos, unsigned int charSize, sf::Font &font);

 //std::shared_ptr<mouseEvent> me;
 //std::shared_ptr<Audio> _audio;
 //std::shared_ptr<Context_Handler> context_Handle;
 //std::shared_ptr<Resized> re;

 mouseEvent *me;
 Audio *_audio;
 Context_Handler *context_Handle;
 Resized* re;

protected:
 const float width = 1080;
 const float height = 720;
 bool movie_Two_is_Greater;
 void setButtons(Buttons &b, float sX, float sY, std::string text, sf::Color &c, sf::Color &out, float outsize, sf::Color &tc, sf::Vector2f &p, float scaleX, float scaleY, float extra);
 void setSwitches(Switch &s, float size, sf::Vector2f pos);
 
public:
 InitialSetup(mouseEvent*, Audio* Audio_Object, Context_Handler* cM_Handle, Resized *resized_Object);
 ~InitialSetup();
 void initializeButtons();
 void init_Debug(Debugging &debug);
 void Setup_Window();
 bool OpenFile(int n);
 bool LoadMovie(int n, sfe::Movie **Movie_to_Load);
 void menuButtonsSettings();
 void Movie2Limits();
};

