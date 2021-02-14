#pragma once
#include<utility>
#include<vector>

#include<FL/Fl.h>
#include<FL/Fl_Widget.h>
#include<FL/fl_draw.H>


class Spaceship :Fl_Widget {
	int x;
	int y;
	int sz;
	Fl_Color lc=FL_BLACK;
	Fl_Color fc = FL_RED;
public:
	Spaceship(int, int,int);
	void draw();
	void move(int, int);
	void set_color(Fl_Color);
	void set_fill_color(Fl_Color);
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
	void move(int,int);
	void set_color(Fl_Color);
	std::pair<int, int> get_pos()const;
};











//Pixel_Laser_beam noch unausgereift
enum class Thickness {								//Bestimmt die Dicke beim Pixel_Laser_beam
	thin, medium, thick
};

class Pixel_Laser_beam :Fl_Widget {
	int x;
	int y;
	int sz;
	Fl_Color lc = FL_BLUE;
	Thickness thickness = Thickness::thick;
	std::vector<std::pair<int, int>>pixels;

public:
	Pixel_Laser_beam(int, int, int);
	void draw();
	void move(int, int);
	void set_color(Fl_Color);
	std::pair<int, int> get_pos();
};