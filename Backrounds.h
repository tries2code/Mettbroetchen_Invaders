#pragma once
#include<FL/Fl.h>
#include<FL/Fl_Widget.h>
#include<FL/fl_draw.H>

#include"Spaceship.h"

class Score_panel :Fl_Widget {  //Shows score while playing
	int x;
	int y;
	int score = 0;
public:
	Score_panel(int, int);
	void draw();
};

class Backround_lv1 :Fl_Widget {
	int x;
	int y;
	int w;
	int h;
public:
	Backround_lv1(int,int,int,int);
	void draw();
};

class Backround_Start_Screen :Fl_Widget {
	int x;
	int y;
	int w;
	int h;
public:
	Backround_Start_Screen(int, int, int, int);
	void draw();
};

class Backround_HS_Screen :Fl_Widget {
	int x;
	int y;
	int w;
	int h;
public:
	Backround_HS_Screen(int, int, int, int);
	void draw();
};

class Backround_GO_Screen :Fl_Widget {
	int x;
	int y;
	int w;
	int h;
public:
	Backround_GO_Screen(int, int, int, int);
	void draw();
};