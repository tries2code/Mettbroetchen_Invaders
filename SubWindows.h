#pragma once
#include<FL/Fl_Window.H>
#include<FL/fl_draw.H>
#include<FL/Fl_Input.H>
#include<FL/Fl_Button.H>

#include"Backrounds.h"

#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<algorithm>

class Record : Fl_Widget{				//Used to write stuff, like records for example. Basically a text Widget
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
	Backround_Start_Screen backround;
	Fl_Button start;
	Record title{ x + width / 10,80,5,45,"Welcome to Mettbrötchen Invaders" };
	Record instr1{ x + width / 10,200,5,30,"Press a/d or <-/-> to move." };
	Record instr2{ x + width / 10,250,5,30,"Press space to shoot." };
	Record instr3{ x + width / 10,380,5,30,"....and lower your expectations or press Esc!" };
	
	Fl_Color fc = FL_DARK_CYAN;

public:
	Start_window(int, int, int, int);
	static void cb_start(Fl_Widget*, void* addr) { ((Start_window*)addr)->start_game(); }
	void start_game();
};

class Highscores :public Fl_Window {
	int x;
	int y;
	int width;
	Backround_HS_Screen backround;
	Fl_Button cont;
	Record hs_title{ x + width / 4,100,5,75,"Highscores" };
	Fl_Color fc = FL_DARK_CYAN;
public:
	Highscores(int, int, int, int, const char*);
	static void cb_cont(Fl_Widget*, void* addr) { ((Highscores*)addr)->continue_game(); }
	void continue_game();
};

class Game_Over : Fl_Window {
	int x;
	int y;
	int width;
	Backround_GO_Screen backround;
	Fl_Button cont;
	Fl_Button quit;
	Fl_Input enter_name;
	Record go_title{ x + 165,150,5,145,"Game Over" };
	Fl_Color fc = FL_DARK_CYAN;
public:
	Game_Over(int, int, int, int, const char*);
	static void cb_cont(Fl_Widget*, void* addr) { ((Game_Over*)addr)->continue_game(); }
	static void cb_quit(Fl_Widget*, void* addr) { ((Game_Over*)addr)->quit_game(); }
	void continue_game();
	void quit_game();
	void save_score();
};