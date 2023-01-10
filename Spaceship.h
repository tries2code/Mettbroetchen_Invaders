#pragma once
#include<utility>
#include<vector>

#include<FL/Fl.H>
#include<FL/Fl_Widget.H>
#include<FL/fl_draw.H>

class Spaceship :Fl_Widget {
	int x;
	int y;
	int start_x;				//original starting position, used for reset_pos()
	int sz;						//size
	Fl_Color lc=FL_BLACK;		//line color
	Fl_Color fc = FL_RED;		//fill color
public:
	Spaceship(int, int,int);
	void draw();
	void move(int);
	void set_color(Fl_Color);
	void set_fill_color(Fl_Color);
	void reset_pos();
	std::pair<int, int> get_pos()const;
};

class Laser_beam :public Fl_Widget {
	int x;
	int y;
	int sz;							//size
	Fl_Color lc = FL_GREEN;
public:
	Laser_beam(int, int, int);
	void draw();
	void move(int);
	void set_color(Fl_Color);
	std::pair<int, int> get_pos()const;
};



