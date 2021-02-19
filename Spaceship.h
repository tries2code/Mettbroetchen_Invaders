#pragma once
#include<utility>
#include<vector>
#include<FL/Fl.h>
#include<FL/Fl_Widget.h>
#include<FL/fl_draw.H>

class Spaceship :Fl_Widget {
	int x;
	int y;
	int start_x;
	int sz;
	Fl_Color lc=FL_BLACK;
	Fl_Color fc = FL_RED;
public:
	Spaceship(int, int,int);
	void draw();
	void move(int);
	void set_color(Fl_Color);
	void set_fill_color(Fl_Color);
	void reset_pos();
	std::pair<int, int> get_pos()const;
};

class Laser_beam :Fl_Widget {
	int x;
	int y;
	int sz;
	Fl_Color lc = FL_GREEN;
public:
	Laser_beam(int, int, int);
	void draw();
	void move(int);
	void set_color(Fl_Color);
	std::pair<int, int> get_pos()const;
};

class Barrier :Fl_Widget {
	int x;
	int y;
	int sz;
	Fl_Color lc = FL_BLACK;
	std::vector<std::pair<int, int>>pixels;
	std::vector<std::pair<int, int>>back_up_pixels;

public:
	Barrier(int, int, int);
	void draw();
	void damage(int,int);
	void restore();
	std::vector<std::pair<int, int>>get_pixels()const;
};


