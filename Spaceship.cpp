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
	fl_line_style(0, 6,0);
	fl_line(x, y, x, y - sz/3);
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


Barrier::Barrier(int a, int b, int s) :Fl_Widget(a, b, a, b), x(a), y(b), sz(s) { //constructor calculates pixels for a barrier
	int part =sz / 50;

	int start_x = x+part * 15;
	int start_y = y+part*10;
	int end_x =x+ part * 35;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 14;
	start_y = y+part * 11;
	end_x = x+part * 36;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 12;
	start_y = y+part * 12;
	end_x = x+part * 38;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 11;
	start_y = y+part * 13;
	end_x = x+part * 39;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 9;
	start_y = y+part * 14;
	end_x = x+part * 41;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 8;
	start_y = y+part * 15;
	end_x = x+part * 42;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 6;
	start_y = y+part * 16;
	end_x = x+part * 44;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 5;
	start_y = y+part * 17;
	end_x = x+part * 45;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 3;
	start_y = y+part * 18;
	end_x = x+part * 47;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part * 2;
	start_y = y+part * 19;
	end_x = x+part * 48;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}
	start_x = x+part ;
	start_y = y+part * 20;
	end_x = x+part * 50;
	while (start_x != end_x) {
		pixels.emplace_back(start_x, start_y);
		++start_x;
	}												//i should do this a bit smarter next time...

	start_x = x+part;
	start_y = y+part*20;
	end_x = x+part*50;
	do {
		pixels.emplace_back(start_x, start_y);
		++start_x;
		if (start_x == end_x && start_y <= (y+part*30)) {
			start_x = x + part;
			++start_y;
		}
	} while (start_x != end_x);

	start_x = x + part;
	start_y = y + part * 30;
	end_x = x + part * 10;
	do {
		pixels.emplace_back(start_x, start_y);
		++start_x;
		if (start_x == end_x && start_y <= (y + part * 40)) {
			start_x = x + part;
			++start_y;
		}
	} while (start_x != end_x);

	start_x = x + part*10;
	start_y = y + part * 40;
	end_x = x + part * 10;
	do {
		pixels.emplace_back(start_x, start_y);
		++start_x;
		if (start_x > end_x) {
			start_x = x + part * 10;
			++end_x;
			--start_y;
		}
		
	} while (start_x<=end_x&&start_y>=(y + part * 30));


	start_x = x + part * 30;
	start_y = y + part * 30;
	end_x = x + part * 40;
	int count = 1;
	do {
		pixels.emplace_back(start_x, start_y);
		++start_x;
		if (start_x >= end_x) {
			start_x = x + part * 30+count;
			++start_y;
			++count;
		}

	} while (start_x != end_x && start_y != (y + part * 40));


	start_x = x + part * 40;
	start_y = y + part * 30;
	end_x = x + part * 50;
	do {
		pixels.emplace_back(start_x, start_y);
		++start_x;
		if (start_x == end_x) {
			start_x = x + part * 40;
			++start_y;
		}

	} while (start_x != end_x && start_y <= (y + part * 40));
	back_up_pixels = pixels;
}
void Barrier::draw() {
	fl_color(lc);
	for (unsigned int i = 0; i < pixels.size(); i++) fl_point(pixels[i].first, pixels[i].second);
}
void Barrier::damage(int a, int b) {
		for (unsigned int i = 0; i < pixels.size(); i++) {
			if ((pixels[i].first == a && pixels[i].second == b) || (pixels[i].first == b && pixels[i].second == a))
				pixels.erase(pixels.begin() + i);
		}
		pixels.shrink_to_fit();
}
void Barrier::restore() {
	pixels = back_up_pixels;
}
std::vector<std::pair<int, int>>Barrier::get_pixels()const {return pixels;}





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