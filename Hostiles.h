#pragma once
#include<cstdlib>
#include<ctime>

#include<FL/Fl_Box.H>
#include<FL/Fl_Widget.h>
#include<FL/Fl_PNG_Image.H>


class Hostile :Fl_Widget {			
	int x;
	int y;
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
	Fl_Box b;
public:
	Hostile(int, int);
	void draw();
	void move(int, int);
	void hide();
	void show();
	bool active();
};