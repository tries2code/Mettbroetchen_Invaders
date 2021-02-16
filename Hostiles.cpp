#include"Hostiles.h"

Hostile::Hostile(int a, int b) :Fl_Widget(a, b, a, b), x(a), y(b),start_x(a),start_y(b), b(x, y, 50, 50) {
	
	int kind = 1 + (rand() % 13);
	switch (kind) {
	case 1:
		this->b.image(im1);		
		start_w = x + 25;
		end_w = start_w + 50;
	break; case 2:
		this->b.image(im2);
		start_w = x;
		end_w = start_w + 80;
	break; case 3:
		this->b.image(im3);
		start_w = x + 20;
		end_w = start_w + 55;
	break; case 4:
		this->b.image(im4);
		start_w = x + 30;
		end_w = start_w + 49;
	break; case 5:
		this->b.image(im5);
		start_w = x + 28;
		end_w = start_w + 52;
	break; case 6:
		this->b.image(im6);
		start_w = x + 23;
		end_w = start_w + 49;
	break; case 7:
		this->b.image(im7);
		start_w = x + 23;
		end_w = start_w + 60;
	break; case 8:
		this->b.image(im8);
		start_w = x + 31;
		end_w = start_w + 42;
	break; case 9:
		this->b.image(im9);
		start_w = x + 30;
		end_w = start_w + 55;
	break; case 10:
		this->b.image(im10);
		start_w = x + 33;
		end_w = start_w + 52;
	break; case 11:
		this->b.image(im11);
		start_w = x + 33;
		end_w = start_w + 45;
	break; case 12:
		this->b.image(im12);
		start_w = x + 35;
		end_w = start_w + 42;
	break; case 13:
		this->b.image(im13);
		start_w = x + 30;
		end_w = start_w + 52;
		break;
	}
	re_start_w = start_w;
	re_end_w = end_w;
	set_a_s();
}
void Hostile::draw() {b.position(x, y);}
void Hostile::move(int a, int b) {
	x += a;
	y += b;
	start_w += a;
	end_w += a;
	set_a_s();
	hide();
	show();
}
void Hostile::reset_pos() {
	x = start_x;
	y = start_y;
	start_w = re_start_w;
	end_w = re_end_w;
	set_a_s();
}
void Hostile::hide() {
	b.deactivate();
	b.hide();
}
void Hostile::show() {
	b.set_active();
	b.show();
}
void Hostile::set_a_s() {
attack_surface.clear();
	int temp = start_w;
	while (temp != end_w) {
		attack_surface.emplace_back(temp, y + 25);
		++temp;
	}
}
std::vector<std::pair<int, int>> Hostile::get_a_s() {return attack_surface;}
int Hostile::get_y() { return y+25; }
bool Hostile::active() {
	if (b.active())return true;
	return false;
}
