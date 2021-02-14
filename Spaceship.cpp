#include"Spaceship.h"


Spaceship::Spaceship(int a, int b, int s) :Fl_Widget(a, b, a, b), x(a), y(b), sz(s) {

}
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
void Spaceship::move(int a, int b){
	x += a;
	y += b;
	this->hide();
	this->show();
}
void Spaceship::set_color(Fl_Color c) { lc = c; }
void Spaceship::set_fill_color(Fl_Color c) { fc = c; }
std::pair<int, int> Spaceship::get_pos()const {
	std::pair<int, int>cannon{ x + sz / 2,y };
	return cannon;
}

Laser_beam::Laser_beam(int a, int b, int s) :Fl_Widget(a, b, a, b), x(a), y(b), sz(s) {}
void Laser_beam::draw() {				
	fl_color(lc);
	fl_line_style(1, 6,0);
	fl_line(x, y, x, y - sz);
}
void Laser_beam::move(int a, int b) {
	x += a;
	y += b;
	draw();
}
void Laser_beam::set_color(Fl_Color c) { lc = c; }
std::pair<int, int> Laser_beam::get_pos()const {
	std::pair<int, int>laser{ x ,y };
	return laser;
}




//Pixel_Laser_beam not really working, maybe a waste of time

Pixel_Laser_beam::Pixel_Laser_beam(int a, int b, int s): Fl_Widget(a, b, a, b), x(a), y(b), sz(s) {
	int temp_x = x;
	int temp_y = y;

	while (temp_y != (y - sz)) {
		switch (thickness) {
		case Thickness::thin:
			pixels.push_back(std::make_pair(temp_x, temp_y));
			break;
		case Thickness::medium:
			pixels.push_back(std::make_pair(temp_x, temp_y));
			pixels.push_back(std::make_pair(temp_x + 1, temp_y));
			break;
		case Thickness::thick:
			pixels.push_back(std::make_pair(temp_x, temp_y));
			pixels.push_back(std::make_pair(temp_x + 1, temp_y));
			pixels.push_back(std::make_pair(temp_x + 2, temp_y));
			break;
		}
		--temp_y;
	}
}
void Pixel_Laser_beam::draw() {
	fl_color(lc);
	for (unsigned int i = 0; i < pixels.size(); i++) fl_point(pixels[i].first, pixels[i].second);
}
void Pixel_Laser_beam::move(int a, int b) {

	for (unsigned int i = 0; i < pixels.size(); i++) {
		pixels[i].first += a;
		pixels[i].second += b;
	}
}
void Pixel_Laser_beam::set_color(Fl_Color c) { lc = c; }
std::pair<int, int> Pixel_Laser_beam::get_pos() {
	std::pair<int, int>laser{ x ,y };
	return laser;
}