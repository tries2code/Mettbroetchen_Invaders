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
	Fl_Color fc = FL_DARK_RED;
public:
	Record(int, int,int,int, std::string);
	void draw();
	void set_color(Fl_Color);
};

class Start_window :public Fl_Window {
	int x;
	int y;
	int width;
	Fl_Button start;
	Record title{ x + width / 10,80,5,45,"Welcome to Mettbrötchen Invaders" };
	Record instr1{ x + width / 10,200,5,30,"Press a/d or <-/-> to move." };
	Record instr2{ x + width / 10,250,5,30,"Press space to shoot." };
	Record instr3{ x + width / 10,450,5,30,"....and lower your expectations" };

public:
	Start_window(int, int, int, int);
	static void cb_start(Fl_Widget*, void* addr) { ((Start_window*)addr)->start_game(); }
	void start_game();
};

class Highscores :public Fl_Window {
	int x;
	int y;
	int width;
	Fl_Button cont;
	Record title{ x + width / 3,40,5,45,"Highscores" };
public:
	Highscores(int, int, int, int, const char*);
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