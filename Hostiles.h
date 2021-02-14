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

	Fl_PNG_Image im1{ "MBs/MB1.png" };
	Fl_PNG_Image im2{ "MBs/MB2.png" };
	Fl_PNG_Image im3{ "MBs/MB3.png" };
	Fl_PNG_Image im4{ "MBs/MB4.png" };
	Fl_PNG_Image im5{ "MBs/MB5.png" };
	Fl_PNG_Image im6{ "MBs/MB6.png" };
	Fl_PNG_Image im7{ "MBs/MB7.png" };
	Fl_PNG_Image im8{ "MBs/MB8.png" };
	Fl_PNG_Image im9{ "MBs/MB9.png" };
	Fl_PNG_Image im10{ "MBs/M10.png" };
	Fl_PNG_Image im11{ "MBs/MB11.png" };
	Fl_PNG_Image im12{ "MBs/MB12.png" };
	Fl_PNG_Image im13{ "MBs/MB13.png" };
	
public:
	Hostile(int, int);
	void draw();
	void move(int, int);
	void reset_pos();
	void hide();
	void show();
	void set_a_s();
	std::vector<std::pair<int, int>> get_a_s();
	bool active();
};