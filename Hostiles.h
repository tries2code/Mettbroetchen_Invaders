#pragma once
#include<cstdlib>
#include<ctime>
#include<utility>
#include<vector>

#include<FL/Fl_Box.H>
#include<FL/Fl_Widget.h>
#include<FL/Fl_PNG_Image.H>
#include<FL/fl_draw.H>


class Hostile :Fl_Widget {			
	int x;
	int y;
	int start_x;
	int start_y;

	int start_w=0;
	int end_w=0;
	int re_start_w=0;
	int re_end_w=0;

	std::vector<std::pair<int, int>>attack_surface;

	Fl_Box b;
public:
	Hostile(int, int);
	void draw();
	void move(int, int);
	void reset_pos();
	void hide();
	void show();
	void redraw();
	void set_a_s();
	std::vector<std::pair<int, int>> get_a_s();
	int get_y();
	bool active();
};