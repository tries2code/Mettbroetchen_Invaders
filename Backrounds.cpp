#include"Backrounds.h"

extern int g_score;

Score_panel::Score_panel(int a, int b):Fl_Widget(a,b,a,b),x(a),y(b) {} //Shows score while playing
void Score_panel::draw() {
	char points[50];
	sprintf_s(points, "%d", g_score);
	fl_color(204, 0, 0);
	fl_font(5, 19);
	fl_draw("Score:", x, y);
	fl_draw(points, x, y+20);
}

Backround_lv1::Backround_lv1(int a, int b, int c, int d) :
	Fl_Widget(a, b, c, d), x(a-50), y(b-50), w(c), h(d) {
	position(x, y);
}
void Backround_lv1::draw() {

	fl_color(FL_DARK_BLUE);				//backround color
	fl_rectf(x, y, w, h);

	fl_color(FL_DARK_RED);				//moon? mars? idk...
	fl_arc(100, 200, 100, 100, 0, 360);
	fl_pie(100, 200, 100, 100, 0, 360);

	fl_color(96, 96, 96);					//Skyline
	fl_rectf(x + 10, 660, 40, 160);
	fl_rectf(x + 60, 650, 60, 160);
	fl_rectf(x + 130, 640, 40, 160);
	fl_rectf(x + 190, 700, 80, 160);
	fl_rectf(x + 280, 620, 30, 190);
	fl_rectf(x + 330, 660, 50, 160);
	fl_rectf(x + 390, 690, 70, 160);
	fl_rectf(x + 480, 630, 30, 190);
	fl_rectf(x + 520, 660, 50, 160);
	fl_rectf(x + 590, 650, 50, 160);
	fl_rectf(x + 660, 640, 40, 160);
	fl_rectf(x + 720, 670, 50, 160);
	fl_rectf(x + 790, 690, 70, 160);
	fl_rectf(x + 870, 660, 60, 160);
	fl_rectf(x + 940, 640, 40, 160);
	fl_rectf(x + 990, 640, 40, 160);
	fl_rectf(x + 1040, 620, 50, 190);

	fl_color(153, 153, 0);
	fl_line_style(2, 6, 0);
	//Windows of first building
	fl_line(15, 670, 45, 670);
	fl_line(15, 680, 33, 680);
	fl_line(15, 690, 45, 690);
	fl_line(15, 700, 45, 700);
	fl_line(15, 710, 20, 710);
	fl_line(39, 710, 45, 710);
	fl_line(15, 720, 45, 720);
	fl_line(15, 730, 45, 730);
	fl_line(15, 740, 45, 740);
	fl_line(27, 750, 45, 750);
	fl_line(15, 760, 45, 760);
	fl_line(15, 770, 45, 770);
	//Windows of second building
	fl_line(68, 660, 112, 660);
	fl_line(68, 670, 112, 670);
	fl_line(68, 680, 112, 680);
	fl_line(68, 690, 112, 690);
	fl_line(68, 700, 102, 700);
	fl_line(80, 710, 112, 710);
	fl_line(68, 720, 112, 720);
	fl_line(68, 730, 112, 730);
	fl_line(68, 740, 112, 740);
	fl_line(68, 750, 112, 750);
	fl_line(68, 760, 75, 760);
	fl_line(92, 760, 112, 760);
	fl_line(68, 770, 112, 770);
	//Windows of third building
	fl_line(135, 650, 169, 650);
	fl_line(135, 660, 169, 660);
	fl_line(135, 670, 169, 670);
	fl_line(135, 680, 169, 680);
	fl_line(135, 690, 169, 690);
	fl_line(135, 700, 169, 700);
	fl_line(135, 710, 169, 710);
	fl_line(135, 720, 169, 720);
	fl_line(135, 730, 169, 730);
	fl_line(135, 740, 169, 740);
	fl_line(135, 750, 169, 750);
	fl_line(135, 760, 169, 760);
	fl_line(135, 770, 169, 770);
	//Windows of forth building
	fl_line(196, 710, 266, 710);
	fl_line(196, 720, 266, 720);
	fl_line(196, 730, 266, 730);
	fl_line(196, 740, 266, 740);
	fl_line(196, 750, 266, 750);
	fl_line(196, 760, 266, 760);
	fl_line(196, 770, 266, 770);
	//Windows of fifth building
	fl_line(285, 630, 308, 630);
	fl_line(285, 640, 308, 640);
	fl_line(285, 650, 308, 650);
	fl_line(285, 660, 308, 660);
	fl_line(285, 670, 308, 670);
	fl_line(285, 680, 308, 680);
	fl_line(285, 690, 308, 690);
	fl_line(285, 700, 308, 700);
	fl_line(285, 710, 308, 710);
	fl_line(285, 720, 308, 720);
	fl_line(285, 730, 308, 730);
	fl_line(285, 740, 308, 740);
	fl_line(285, 750, 308, 750);
	fl_line(285, 760, 308, 760);
	fl_line(285, 770, 308, 770);
	//Windows of sixth building
	fl_line(334, 670, 377, 670);
	fl_line(334, 680, 367, 680);
	fl_line(346, 690, 377, 690);
	fl_line(334, 700, 377, 700);
	fl_line(334, 710, 377, 710);
	fl_line(334, 720, 377, 720);
	fl_line(334, 730, 377, 730);
	fl_line(334, 740, 345, 740);
	fl_line(358, 740, 377, 740);
	fl_line(334, 750, 377, 750);
	fl_line(334, 760, 377, 760);
	fl_line(334, 770, 377, 770);
	//Windows of seventh building
	fl_line(397, 700, 455, 700);
	fl_line(397, 710, 455, 710);
	fl_line(397, 720, 455, 720);
	fl_line(397, 730, 455, 730);
	fl_line(397, 740, 455, 740);
	fl_line(397, 750, 455, 750);
	fl_line(397, 760, 455, 760);
	fl_line(397, 770, 455, 770);
	//Windows of eigth building
	fl_line(485, 640, 505, 640);
	fl_line(485, 650, 505, 650);
	fl_line(485, 660, 505, 660);
	fl_line(485, 670, 505, 670);
	fl_line(485, 680, 505, 680);
	fl_line(485, 690, 505, 690);
	fl_line(485, 700, 505, 700);
	fl_line(485, 710, 505, 710);
	fl_line(485, 720, 505, 720);
	fl_line(485, 730, 505, 730);
	fl_line(485, 740, 505, 740);
	fl_line(485, 750, 505, 750);
	fl_line(485, 760, 505, 760);
	fl_line(485, 770, 505, 770);
	//Windows of ninth building
	fl_line(523, 670, 565, 670);
	fl_line(523, 680, 565, 680);
	fl_line(523, 690, 565, 690);
	fl_line(523, 700, 565, 700);
	fl_line(523, 710, 535, 710);
	fl_line(547, 710, 565, 710);
	fl_line(523, 720, 565, 720);
	fl_line(523, 730, 565, 730);
	fl_line(523, 740, 565, 740);
	fl_line(523, 750, 565, 750);
	fl_line(523, 760, 565, 760);
	fl_line(523, 770, 565, 770);
	//Windows of tenth building
	fl_line(593, 660, 635, 660);
	fl_line(593, 670, 635, 670);
	fl_line(593, 680, 635, 680);
	fl_line(593, 690, 635, 690);
	fl_line(593, 700, 635, 700);
	fl_line(593, 710, 615, 710);
	fl_line(629, 710, 635, 710);
	fl_line(593, 720, 635, 720);
	fl_line(605, 730, 635, 730);
	fl_line(593, 740, 635, 740);
	fl_line(593, 750, 635, 750);
	fl_line(593, 760, 635, 760);
	fl_line(593, 770, 635, 770);
	//Windows of eleventh building
	fl_line(665, 650, 695, 650);
	fl_line(665, 660, 695, 660);
	fl_line(665, 670, 695, 670);
	fl_line(665, 680, 695, 680);
	fl_line(665, 690, 695, 690);
	fl_line(665, 700, 695, 700);
	fl_line(665, 710, 695, 710);
	fl_line(665, 720, 695, 720);
	fl_line(665, 730, 695, 730);
	fl_line(665, 740, 695, 740);
	fl_line(665, 750, 695, 750);
	fl_line(665, 760, 695, 760);
	fl_line(665, 770, 695, 770);
	//Windows of twelveth building
	fl_line(723, 680, 765, 680);
	fl_line(723, 690, 755, 690);
	fl_line(723, 700, 765, 700);
	fl_line(723, 710, 765, 710);
	fl_line(723, 720, 765, 720);
	fl_line(723, 730, 745, 730);
	fl_line(723, 740, 765, 740);
	fl_line(723, 750, 765, 750);
	fl_line(723, 760, 765, 760);
	fl_line(723, 770, 765, 770);
	//Windows of thirteenth building
	fl_line(797, 700, 857, 700);
	fl_line(797, 710, 857, 710);
	fl_line(797, 720, 857, 720);
	fl_line(797, 730, 857, 730);
	fl_line(797, 740, 857, 740);
	fl_line(797, 750, 857, 750);
	fl_line(797, 760, 857, 760);
	fl_line(797, 770, 857, 770);
	//Windows of fourteenth building
	fl_line(873, 670, 933, 670);
	fl_line(873, 680, 933, 680);
	fl_line(873, 690, 933, 690);
	fl_line(873, 700, 933, 700);
	fl_line(897, 710, 933, 710);
	fl_line(873, 720, 933, 720);
	fl_line(873, 730, 915, 730);
	fl_line(873, 740, 933, 740);
	fl_line(873, 750, 933, 750);
	fl_line(873, 760, 933, 760);
	fl_line(873, 770, 933, 770);
	//Windows of fiveteenth building
	fl_line(945, 650, 975, 650);
	fl_line(945, 660, 975, 660);
	fl_line(945, 670, 975, 670);
	fl_line(945, 680, 975, 680);
	fl_line(945, 690, 975, 690);
	fl_line(945, 700, 975, 700);
	fl_line(945, 710, 975, 710);
	fl_line(945, 720, 975, 720);
	fl_line(945, 730, 975, 730);
	fl_line(945, 740, 975, 740);
	fl_line(945, 750, 975, 750);
	fl_line(945, 760, 975, 760);
	fl_line(945, 770, 975, 770);
	//Windows of sixteenth building
	fl_line(995, 650, 1025, 650);
	fl_line(995, 660, 1025, 660);
	fl_line(995, 670, 1025, 670);
	fl_line(995, 680, 1025, 680);
	fl_line(995, 690, 1025, 690);
	fl_line(995, 700, 1025, 700);
	fl_line(995, 710, 1025, 710);
	fl_line(995, 720, 1025, 720);
	fl_line(995, 730, 1025, 730);
	fl_line(995, 740, 1025, 740);
	fl_line(995, 750, 1025, 750);
	fl_line(995, 760, 1025, 760);
	fl_line(995, 770, 1025, 770);
	//Windows of seventeenth building
	fl_line(1044, 630, 1085, 630);
	fl_line(1044, 640, 1085, 640);
	fl_line(1044, 650, 1085, 650);
	fl_line(1044, 660, 1085, 660);
	fl_line(1044, 670, 1085, 670);
	fl_line(1044, 680, 1055, 680);
	fl_line(1068, 680, 1085, 680);
	fl_line(1044, 690, 1085, 690);
	fl_line(1044, 700, 1085, 700);
	fl_line(1044, 710, 1085, 710);
	fl_line(1056, 720, 1085, 720);
	fl_line(1044, 730, 1085, 730);
	fl_line(1044, 740, 1085, 740);
	fl_line(1044, 750, 1085, 750);
	fl_line(1044, 760, 1085, 760);
	fl_line(1044, 770, 1085, 770);		//maybe i should have made a building class instead....

	//Hotel Signs
	fl_color(204, 0, 0);
	fl_font(5, 19);
	fl_draw("HOTEL", 797, 692);
	fl_font(1, 19);
	fl_draw("HOTEL", 392, 692);
	fl_font(7, 23);
	fl_draw("HOTEL", 195, 705);

}

Backround_Start_Screen::Backround_Start_Screen(int a, int b, int c, int d) :
	Fl_Widget(a, b, c, d), x(a - 50), y(b - 50), w(c), h(d) {
	position(x, y);
}
void Backround_Start_Screen::draw() {
	fl_color(FL_DARK_BLUE);					//backround color
	fl_rectf(x, y, w, h);

	fl_color(96, 96, 96);					//Buildings

	fl_rectf(x - 10, 550, 300, 300);
	fl_rectf(x + 350, 700, 550, 300);
	fl_rectf(x + 950, 600, 400, 300);

	fl_color(153, 153, 0);					//Windows of Buildings

	fl_rectf(x - 10, 575, 50, 50);
	fl_rectf(x + 65, 575, 50, 50);
	fl_rectf(x + 140, 575, 50, 50);
	fl_rectf(x + 215, 575, 50, 50);
	fl_rectf(x - 10, 650, 50, 50);
	fl_rectf(x + 65, 650, 50, 50);
	fl_rectf(x + 140, 650, 50, 50);
	fl_rectf(x + 215, 650, 50, 50);
	fl_rectf(x - 10, 725, 50, 50);
	fl_rectf(x + 65, 725, 50, 50);
	fl_rectf(x + 140, 725, 50, 50);
	fl_rectf(x + 215, 725, 50, 50);
	fl_rectf(x - 10, 800, 50, 50);
	fl_rectf(x + 65, 800, 50, 50);
	fl_rectf(x + 140, 800, 50, 50);
	fl_rectf(x + 215, 800, 50, 50);

	fl_rectf(x + 375, 725, 50, 50);
	fl_rectf(x + 450, 725, 50, 50);
	fl_rectf(x + 525, 725, 50, 50);
	fl_rectf(x + 600, 725, 50, 50);
	fl_rectf(x + 675, 725, 50, 50);
	fl_rectf(x + 750, 725, 50, 50);
	fl_rectf(x + 825, 725, 50, 50);
	fl_rectf(x + 375, 800, 50, 50);
	fl_rectf(x + 450, 800, 50, 50);
	fl_rectf(x + 525, 800, 50, 50);
	fl_rectf(x + 600, 800, 50, 50);
	fl_rectf(x + 675, 800, 50, 50);
	fl_rectf(x + 750, 800, 50, 50);
	fl_rectf(x + 825, 800, 50, 50);

	fl_rectf(x + 975, 655, 50, 50);
	fl_rectf(x + 1050, 655, 50, 50);
	fl_rectf(x + 1125, 655, 50, 50);
	fl_rectf(x + 975, 730, 50, 50);
	fl_rectf(x + 1050, 730, 50, 50);
	fl_rectf(x + 1125, 730, 50, 50);
	fl_rectf(x + 975, 805, 50, 50);
	fl_rectf(x + 1050, 805, 50, 50);
	fl_rectf(x + 1125, 805, 50, 50);

	fl_color(204, 0, 0);
	fl_font(7, 210);
	fl_draw("HO", 1000, 630);
}