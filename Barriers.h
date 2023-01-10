#pragma once
#include<FL/Fl.H>
#include<FL/Fl_Widget.H>
#include<FL/fl_draw.H>
#include<vector>

//Barrier parts, Look at Barrier_Doc.JPEG to learn more
struct Barrier_part :Fl_Widget { //Part Base-Struct
	int x;
	int y;
	int sz;
	Fl_Color fc = FL_BLACK;
	Barrier_part(int, int, int);
	void set_color(Fl_Color);
};

struct ul1 :Barrier_part {	//Upper left 1
	ul1(int, int, int);
	void draw();
};
struct ul2 :Barrier_part {	//Upper left 2
	ul2(int, int, int);
	void draw();
};
struct ur1 :Barrier_part {	//Upper right 1
	ur1(int, int, int);
	void draw();
};
struct ur2 :Barrier_part {	//Upper right 2
	ur2(int, int, int);
	void draw();
};
struct idl :Barrier_part { //inside down left
	idl(int, int, int);
	void draw();
};
struct idr :Barrier_part { //inside down right
	idr(int, int, int);
	void draw();
};
struct re :Barrier_part { //rectangle(usied multiple times)
	re(int, int, int);
	void draw();
};

//whole Barrier
class Barrier :Fl_Widget {
	int x;
	int y;
	int sz;
	std::vector<Barrier_part*> vec;
public:
	Barrier(int, int, int);
	int get_x();
	void draw();
	void damage(int, int);
	void restore();
};
