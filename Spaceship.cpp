#include"Spaceship.h"


Spaceship::Spaceship(int a, int b, int s) :Fl_Widget(a, b, a, b), x(a), y(b),start_x(a), sz(s) {}
void Spaceship::draw() {
	double xx = x;
	double yy = y;
	double ssz = sz;
	fl_color(fc);
	fl_begin_complex_polygon();
	fl_vertex(xx,yy+ssz);
	fl_vertex(xx+ssz/4,yy+ssz/16*10);
	fl_vertex(xx+ssz/4,yy+ssz/2);
	fl_vertex(xx+ssz/2,yy);
	fl_vertex(xx + ssz / 16*12, yy+ssz/2);
	fl_vertex(xx + ssz / 16 * 12, yy + ssz / 16*10);
	fl_vertex(xx + ssz , yy + ssz );
	fl_vertex(xx + ssz / 2, yy + ssz / 16*12);
	fl_end_complex_polygon();

	fl_color(lc);
	fl_line_style(0, 3, 0);
	fl_line(x, y+sz,x+sz/4,y+sz/16*10);
	fl_line(x + sz / 4, y + sz / 16 * 10, x + sz / 4, y + sz / 2);
	fl_line( x + sz / 4, y + sz / 2,x+sz/2,y);
	fl_line(x + sz / 2, y, x+sz/16*12, y+sz/2);
	fl_line( x + sz / 16 * 12, y + sz / 2,x+sz/16*12,y+sz/16*10);
	fl_line( x + sz / 16 * 12, y + sz / 16 * 10,x+sz,y+sz);
	fl_line( x + sz, y + sz,x+sz/2,y+sz/16*12);
	fl_line(x + sz / 2, y + sz / 16 * 12, x, y + sz);
}
void Spaceship::move(int a) {
	x += a;
	deactivate();
	position(x, y);
	activate();
}
void Spaceship::set_color(Fl_Color c) { lc = c; }
void Spaceship::set_fill_color(Fl_Color c) { fc = c; }
void Spaceship::reset_pos() {
	x = start_x;
	this->hide();
	this->show();
}
std::pair<int, int> Spaceship::get_pos()const {
	std::pair<int, int>cannon{ x + sz / 2,y };
	return cannon;
}

Laser_beam::Laser_beam(int a, int b, int s) :
	Fl_Widget(a, b, a, b), x(a), y(b), sz(s) {}
void Laser_beam::draw() {
		fl_color(lc);
		fl_line_style(0, 6, 0);
		fl_line(x, y, x, y - sz);
}

void Laser_beam::move(int b) {
	y += b;
	draw();
}
void Laser_beam::set_color(Fl_Color c) { lc = c; }
std::pair<int, int> Laser_beam::get_pos()const {
	std::pair<int, int>laser{ x ,y-sz/3 };
	return laser;
}
