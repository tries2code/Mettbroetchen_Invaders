#pragma once
#include<FL/Fl_Window.h>
#include<FL/fl_draw.H>
#include<FL/Fl_Input.H>
#include<FL/Fl_Button.H>

#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<algorithm>

class Record : Fl_Widget{
	int x;
	int y;
	int font_face;
	int font_size;
	std::string name;
public:
	Record(int, int,int,int, std::string);
	void draw();
};

class Highscores :public Fl_Window {
	int x;
	int y;
	int width;
	Fl_Button cont;
	Record title{ x + width / 3,40,5,45,"Highscores" };
public:
	Highscores(int, int, int, int, const char*);
	~Highscores(){}
	static void cb_cont(Fl_Widget*, void* addr) { ((Highscores*)addr)->continue_game(); }
	void continue_game();
};

class Game_Over : Fl_Window {
	int x;
	int y;
	int width;
	Fl_Button cont;
	Fl_Button quit;
	Fl_Input enter_name;
	Record title{ x + width / 3,40,5,45,"Game Over" };
public:
	Game_Over(int, int, int, int, const char*);
	static void cb_cont(Fl_Widget*, void* addr) { ((Game_Over*)addr)->continue_game(); }
	static void cb_quit(Fl_Widget*, void* addr) { ((Game_Over*)addr)->quit_game(); }
	void continue_game();
	void quit_game();
	void save_score();
};