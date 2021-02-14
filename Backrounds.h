#pragma once
#include<FL/Fl.h>
#include<FL/Fl_Widget.h>
#include<FL/fl_draw.H>

class Backround_lv1 :Fl_Widget {
	int x;
	int y;
	int w;
	int h;
public:
	Backround_lv1(int,int,int,int);
	void draw();
};