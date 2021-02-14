#include"Hostiles.h"



Hostile::Hostile(int a, int b) :Fl_Widget(a, b, a, b), x(a), y(b),  b(x, y, 100, 100) {
	
	int kind = 1 + (rand() % 13);

	switch (kind) {
	case 1:
		this->b.image(im1);		
		break; case 2:
		this->b.image(im2);
	break; case 3:
		this->b.image(im3);
	break; case 4:
		this->b.image(im4);
	break; case 5:
		this->b.image(im5);
	break; case 6:
		this->b.image(im6);
	break; case 7:
		this->b.image(im7);
	break; case 8:
		this->b.image(im8);
	break; case 9:
		this->b.image(im9);
	break; case 10:
		this->b.image(im10);
	break; case 11:
		this->b.image(im11);
	break; case 12:
		this->b.image(im12);
	break; case 13:
		this->b.image(im13);
		break;
	}
}
void Hostile::draw() {
	
	b.position(x, y);
}
void Hostile::move(int a, int b) {
	x += a;
	y += b;
	this->b.hide();
	this->b.show();

}
void Hostile::hide() {
	b.deactivate();
	b.hide();
}
void Hostile::show() {
	b.set_active();
	b.show();
}
bool Hostile::active() {
	if (b.active())return true;
	return false;
}
