#include"Barriers.h"

//look at Barriers.h and/or Barrier_Doc.JPEG for further comments 

Barrier_part::Barrier_part(int a, int b, int s) :Fl_Widget(a, b, a, b), x(a), y(b), sz(s) {}
void Barrier_part::set_color(Fl_Color c) { fc = c; }

ul1::ul1(int a, int b, int s) : Barrier_part(a, b, s) {}
void ul1::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx, dy + s / 5);
	fl_vertex(dx + s / 5, dy + s / 5);
	fl_vertex(dx + s / 5, (dy + s / 5) - s / 5 / 5 * 4);
	fl_end_complex_polygon();
}
ul2::ul2(int a, int b, int s) : Barrier_part(a, b, s) {}
void ul2::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx , (dy + s / 5) - s / 5 / 5 * 4);
	fl_vertex(dx + s / 5 / 2, dy);
	fl_vertex(dx + s / 5 , dy);
	fl_vertex(dx + s / 5 , dy+s/5);
	fl_vertex(dx , dy + s / 5);
	fl_end_complex_polygon();
}
ur1::ur1(int a, int b, int s) : Barrier_part(a, b, s) {}
void ur1::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx, (dy + s / 5)- s / 5 / 5 * 4);
	fl_vertex(dx, dy + s / 5 );
	fl_vertex(dx+s/5, dy + s / 5);

	fl_end_complex_polygon();
}
ur2::ur2(int a, int b, int s) : Barrier_part(a, b, s) {}
void ur2::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx, dy);
	fl_vertex(dx + s / 5 / 5, dy);
	fl_vertex(dx+s/5, (dy + s / 5) - s / 5 / 5 * 4);
	fl_vertex(dx + s / 5, dy + s / 5);
	fl_vertex(dx, dy + s / 5);
	fl_end_complex_polygon();
}
idl::idl(int a, int b, int s) : Barrier_part(a, b, s) {}
void idl::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx, dy);
	fl_vertex(dx+s/5, dy);
	fl_vertex(dx, dy + s / 5);
	fl_end_complex_polygon();
}
idr::idr(int a, int b, int s) : Barrier_part(a, b, s) {}
void idr::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx, dy);
	fl_vertex(dx + s / 5, dy);
	fl_vertex(dx+s/5, dy + s / 5);
	fl_end_complex_polygon();
}
re::re(int a, int b, int s) : Barrier_part(a, b, s) {}
void re::draw() {
	double dx = x;
	double dy = y;
	double s = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(dx, dy);
	fl_vertex(dx + s / 5, dy);
	fl_vertex(dx + s / 5, dy + s / 5);
	fl_vertex(dx , dy + s / 5);

	fl_end_complex_polygon();
}

Barrier::Barrier(int a, int b, int s) :Fl_Widget(a, b, a, b), x(a), y(b), sz(s){
	//A Barrier is composed of several barrier Parts
	//Look at Barriers_Doc.JPEG to see how the Barriers are composed
ul1 * ulo = new ul1(x,y + sz / 5,sz);
ul2* ult = new ul2(x + sz / 5, y + sz / 5, sz);
idl* idll = new idl(x + sz / 5, y + sz / 5 * 3,sz);
ur1* uro = new ur1(x + sz/5*4, y + sz / 5, sz);
ur2* urt = new ur2(x + sz / 5 * 3, y + sz / 5, sz);
idr* idrr = new idr(x + sz / 5 * 3, y + sz / 5 * 3, sz);
re* re1 = new re(x + sz / 5 * 2, y+sz/5, sz);
re* re2 = new re(x , y + sz / 5*2, sz);
re* re3 = new re(x+sz/5, y + sz / 5 * 2, sz);
re* re4 = new re(x + sz / 5*2, y + sz / 5 * 2, sz);
re* re5 = new re(x + sz / 5 * 3, y + sz / 5 * 2, sz);
re* re6 = new re(x + sz / 5 * 4, y + sz / 5 * 2, sz);
re* re7 = new re(x, y + sz / 5 * 3, sz);
re* re8 = new re(x + sz / 5 * 4, y + sz / 5 * 3, sz);

vec.push_back(ulo);
vec.push_back(ult);
vec.push_back(idll);
vec.push_back(uro);
vec.push_back(urt);
vec.push_back(idrr);
vec.push_back(re1);
vec.push_back(re2);
vec.push_back(re3);
vec.push_back(re4);
vec.push_back(re5);
vec.push_back(re6);
vec.push_back(re7);
vec.push_back(re8);
}
int Barrier::get_x() { return x; }
void Barrier::draw() {}
void Barrier::damage(int a, int b) {
	for (unsigned int i = 0; i < vec.size(); ++i) if (vec[i]->x == a && vec[i]->y == b)vec[i]->set_color(FL_DARK_BLUE);
}
void Barrier::restore() {
	for (unsigned int i = 0; i < vec.size(); ++i)vec[i]->set_color(FL_BLACK);
}

