#include"SubWindows.h"
#include"Spaceship.h"
#include"Backrounds.h"
#include"Hostiles.h"
#include"Barriers.h"

#include<FL/Fl_Double_Window.H>

#include<thread>
#include<map>


std::vector<int>ys{ 560,570,580 };		//for barrier damage coords
std::vector<int>yss{ 560,570 };			//for barrier damage coords

//Global Variables in uses, starting with g_
int g_score = 0;
bool g_game_active = true;			//turns false when a hostile reaches a position where it cant be killed anymore. stops the game.
bool g_game_restart = false;
std::string g_name = "unknown";
Highscores* g_hs = nullptr;
Game_Over* g_go = nullptr;
std::map<int, std::vector<int>>g_d_coords;				//barrier damage coords
std::map<int, std::vector<int>>g_d_coords_backup;
class MB_Invaders :public Fl_Double_Window {

	double time = 0.0025;				//timespan for reoccuring events
	double hostile_time = 2;			//timespan for adding new rows of hostiles(will be increased to 8 after first run)
	double hostile_moving_speed = 2.5;
	int hostile_space = 120;			//distance between hostiles( gets incresed and reseted)
	int hostile_movement = 1;			//handles hostile moving pattern, gets increased and reseted
	int hostile_row_start = 0;			//iterating value for std::vector<Hostile*>hostiles
	int hostile_row_end = 10;			//iterating value for std::vector<Hostile*>hostiles
	int lcd = 0;						//laser cool down
	int x;
	int y;
	int length;
	int sz;								//handles size of things
	Fl_Button check_hs;					//look at highscores
	Score_panel score;

	Backround_lv1 backround;
	Spaceship ship;
	std::vector<Laser_beam*>lasers;		//contains shots
	std::vector<Barrier*>barriers;
	std::vector<Hostile*>hostiles;
	



public:
	MB_Invaders(int, int, int, int, int, const char*);
	static void move_lasers(void*);
	static void add_hostiles(void*);
	static void move_hostiles(void*);
	static void kill_hostiles(void*);
	static void speed_up(void*);
	static void cool_down(void*);
	static void cb_hs(Fl_Widget*, void* addr) { ((MB_Invaders*)addr)->view_highscores(); }
	int handle(int);
	void view_highscores();
	void reset();
};
MB_Invaders::MB_Invaders(int a, int b, int w, int h, int s, const char* title) :
	Fl_Double_Window(a, b, w, h, title), x(a), y(b), length(w), sz(s),
	ship(525, 650, sz), check_hs(length - 95, y + 50, 90, 30, "Highscores"),
	backround(0, 0, w / 12 * 11 + 2, h), score(length - 95, y + 20)
{
	check_hs.clear_visible_focus();		//prevents the button from being pushed by space- or enter key
	check_hs.callback(cb_hs, this);
	check_hs.labelfont(5);
	check_hs.labelcolor(FL_DARK_CYAN);
	check_hs.box(FL_PLASTIC_UP_FRAME);
	
	for (unsigned int i = 0; i < 10; ++i) {							//adds barriers
		Barrier* x = new Barrier{ 75 + (100 * (int)i),550,sz };
		barriers.push_back(x);

		//am map to control barrier damage progress
		g_d_coords.insert(std::pair<int, std::vector<int>>(75 + (100 * (int)i), ys));
		g_d_coords.insert(std::pair<int, std::vector<int>>(85 + (100 * (int)i), ys));
		g_d_coords.insert(std::pair<int, std::vector<int>>(95 + (100 * (int)i), yss));
		g_d_coords.insert(std::pair<int, std::vector<int>>(105 + (100 * (int)i), ys));
		g_d_coords.insert(std::pair<int, std::vector<int>>(115 + (100 * (int)i), ys));
	}
	g_d_coords_backup = g_d_coords;


	hostiles.reserve(150);
	for (unsigned int i = 0; i < 150; ++i) {		//for some reason, Hostiles have to be created inside the constructor
		Hostile* x = new Hostile{ hostile_space ,100 };
		hostiles.push_back(x);
		hostiles[hostiles.size() - 1]->hide();
		hostile_space += 100;

		if (hostile_space == 1020) hostile_space = 120;
	}

	Fl::add_timeout(time, move_lasers, (void*)this);
	Fl::add_timeout(hostile_time, add_hostiles, (void*)this);					//actually just makes hostiles visible and active
	Fl::add_timeout(hostile_moving_speed, move_hostiles, (void*)this);			//moves only active hostiles
	Fl::add_timeout(time, kill_hostiles, (void*)this);
	Fl::add_timeout(time, speed_up, (void*)this);
	Fl::add_timeout(1, cool_down, (void*)this);

	position(x, y);						//Window-Position
	size_range(w, h, w, h);				//locks Window-Size
	show();
}
void MB_Invaders::move_lasers(void* addr) {

	MB_Invaders* mbiw = (MB_Invaders*)addr;
	Fl::add_timeout(mbiw->time, move_lasers, addr);

	if (g_game_active) {

		for (unsigned int i = 0; i < mbiw->lasers.size(); ++i) {
			
			mbiw->lasers[i]->move(-5);								//projectile moves
			std::thread redrawer(Fl::redraw);

			if (mbiw->lasers[i]->get_pos().second <= 0) {			//projectile gets deleted when it reaches the top
				Laser_beam* x = mbiw->lasers[i];
				delete x;
				mbiw->lasers.erase(mbiw->lasers.begin() + i);
				Fl::redraw();
			}

			if (mbiw->lasers[i]->get_pos().second <= 580 && mbiw->lasers[i]->get_pos().second >= 560) {		//Checks if projectile is in y_range of a barrier
				int pos_x = mbiw->lasers[i]->get_pos().first-5;
				if (g_d_coords[pos_x].size()) {																//checks if projectile is in x_range of a barrierpart which hasnt been damaged yet

					for (unsigned int j = 0; j < mbiw->barriers.size(); ++j) {								//Iterates through all Barriers,... yeah, i know...

						if (pos_x >= mbiw->barriers[j]->get_x() && pos_x <= mbiw->barriers[j]->get_x() + 50) {
							mbiw->barriers[j]->damage(pos_x, g_d_coords[pos_x].back());						//"damages" barrier
							g_d_coords[pos_x].pop_back();

							Laser_beam* x = mbiw->lasers[i];												//deletes projectile
							delete x;
							mbiw->lasers.erase(mbiw->lasers.begin() + i);
							mbiw->lasers.shrink_to_fit();
							break;
						}
					}
				}
				Fl::redraw();
			}
			redrawer.join();
		}
	}
}
void MB_Invaders::add_hostiles(void* addr) {						//actually just makes hostiles visible and active

	MB_Invaders* mbiw = (MB_Invaders*)addr;

	if (g_game_active) {

		for (; mbiw->hostile_row_start < mbiw->hostile_row_end; ++mbiw->hostile_row_start)
			mbiw->hostiles[mbiw->hostile_row_start]->show();

		mbiw->hostile_row_end += 10;

		if (mbiw->hostile_row_start >= 150) {
			mbiw->hostile_row_start = 0;
			mbiw->hostile_row_end = 10;
		}
		if (mbiw->hostile_time == 2)mbiw->hostile_time = 10;
	}
	Fl::add_timeout(mbiw->hostile_time, add_hostiles, addr);

}
void MB_Invaders::move_hostiles(void* addr) {

	MB_Invaders* mbiw = (MB_Invaders*)addr;
	Fl::add_timeout(mbiw->hostile_moving_speed, move_hostiles, addr);

	if (g_game_active) {

		if (mbiw->hostile_movement > 8)mbiw->hostile_movement = 1;

		for (unsigned int i = 0; i < mbiw->hostiles.size(); ++i) {
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement < 4)mbiw->hostiles[i]->move(20, 0);
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement == 4)mbiw->hostiles[i]->move(0, 50);
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement > 4 && mbiw->hostile_movement < 8)mbiw->hostiles[i]->move(-20, 0);
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement == 8)mbiw->hostiles[i]->move(0, 50);
			if (mbiw->hostiles[i]->get_y() > 650) g_game_active = false;
		}
		++mbiw->hostile_movement;

		if (!g_game_active) {
			if (g_go)delete g_go;
			g_go = new Game_Over{ 50, 50, 1200, 850,"Game Over" };
		}
	}
	if (g_game_restart)mbiw->reset();
}
void MB_Invaders::kill_hostiles(void* addr) {					//this is where hostiles and laser-projectiles get deleted/hidden in case of a hit

	MB_Invaders* mbiw = (MB_Invaders*)addr;
	Fl::add_timeout(mbiw->time, kill_hostiles, addr);
	if (g_game_active) {
		for (unsigned int i = 0; i < mbiw->hostiles.size(); ++i) {					//check every hostile
			std::vector<std::pair<int, int>> curr_hostile_a_s = mbiw->hostiles[i]->get_a_s();	//get hostiles attack surface range

			for (unsigned int j = 0; j < curr_hostile_a_s.size(); j++) {			//check current hostile attack surface
				for (unsigned int k = 0; k < mbiw->lasers.size(); ++k) {			//check every laser projectile
					std::pair<int, int>curr_laser_pos = mbiw->lasers[k]->get_pos();	//get current laser projectile position
					if (curr_hostile_a_s[j].first == curr_laser_pos.first && curr_hostile_a_s[j].second > curr_laser_pos.second) { //we have a hit

						mbiw->hostiles[i]->hide();					//hide hostile
						mbiw->hostiles[i]->reset_pos();				//put it back in its original position
						Laser_beam* x = mbiw->lasers[k];			//get a pointer to the hitting laser and delete it
						delete x;
						mbiw->lasers.erase(mbiw->lasers.begin() + k);
						mbiw->lasers.shrink_to_fit();
						++g_score;
					}
				}
			}
			//Here is where Hostiles meet barriers
			if (curr_hostile_a_s[0].second+50 >= 560) {
				int pos_x_start = curr_hostile_a_s[0].first- curr_hostile_a_s[0].first%5+5;
				int pos_x_end = curr_hostile_a_s[curr_hostile_a_s.size() - 1].first- curr_hostile_a_s[curr_hostile_a_s.size() - 1].first%5+5;
				for (unsigned int j = 0; j < mbiw->barriers.size(); j++) {
					if (pos_x_start >= mbiw->barriers[j]->get_x() && pos_x_start <= mbiw->barriers[j]->get_x() + 50&& g_d_coords[pos_x_start].size()) {		//checks if an undamged barrier part is present
						mbiw->barriers[j]->damage(pos_x_start, g_d_coords[pos_x_start].front());
						g_d_coords[pos_x_start].erase(g_d_coords[pos_x_start].begin());
						int temp = pos_x_start+10;
						while (temp != pos_x_end) {						//this while loop continues the damge on the entire attack surface of a hostile
							if (g_d_coords[temp].size()) {
								mbiw->barriers[j]->damage(temp, g_d_coords[temp].front());
								g_d_coords[temp].erase(g_d_coords[temp].begin());
							}
							if (!g_d_coords[temp].size())break;
							temp += 10;
						}
						mbiw->hostiles[i]->hide();					//hide hostile
						mbiw->hostiles[i]->reset_pos();				//put it back in its original position
						break;
					}
					//same as above, but from the opposing end of a hostiles attacksurface
					else if (pos_x_end >= mbiw->barriers[j]->get_x() && pos_x_end <= mbiw->barriers[j]->get_x() + 50 && g_d_coords[pos_x_start].size()) {
						mbiw->barriers[j]->damage(pos_x_end, g_d_coords[pos_x_end].front());
						g_d_coords[pos_x_end].erase(g_d_coords[pos_x_end].begin());

						int temp = pos_x_end -10;
						while (temp != pos_x_start) {
							if (g_d_coords[temp].size()) {
								mbiw->barriers[j]->damage(temp, g_d_coords[temp].front());
								g_d_coords[temp].erase(g_d_coords[temp].begin());
							}
							if (!g_d_coords[temp].size())break;
							temp -= 10;
						}
						mbiw->hostiles[i]->hide();					//hide hostile
						mbiw->hostiles[i]->reset_pos();				//put it back in its original position
						break;
					}
				}
			}
		}
	}
}
void MB_Invaders::speed_up(void* addr) {					//increases speed of hostiles depending on the score

	MB_Invaders* mbiw = (MB_Invaders*)addr;
	Fl::add_timeout(mbiw->time, speed_up, addr);

	if (g_score > 75) {
		mbiw->hostile_moving_speed = 2.10;
		mbiw->hostile_time = 8;
	}
	if (g_score > 150) {
		mbiw->hostile_moving_speed = 1.8;
		mbiw->hostile_time = 6;
	}
	if (g_score > 225) {
		mbiw->hostile_moving_speed = 1.2;
		mbiw->hostile_time = 4;
	}
}
void MB_Invaders::cool_down(void* addr) {
	MB_Invaders* mbiw = (MB_Invaders*)addr;
	Fl::add_timeout(1, cool_down, addr);

	if (g_game_active && mbiw->lcd > 0) {
		--mbiw->lcd;
	}
}
int MB_Invaders::handle(int event) {										//fltk handle for keyboard input
	int ret = Fl_Window::handle(event);										//Needed for Mouse-Klick Events. Can be used as return value

	if (g_game_active && event == FL_KEYDOWN) {

		switch (Fl::event_key()) {
		case FL_Escape:
			exit(1);
		case FL_Left:case 97:
			if (ship.get_pos().first > x - 25)ship.move(-10);				//move to the left
			break;
		case FL_Right:case 100:
			if (ship.get_pos().first < length / 12 * 11 - 30)ship.move(10);	//move to the right
			break;
		case 32:															//shots been fired
			if (lcd == 0) {													//...if laser cooldown is 0
				std::pair<int, int>shot{ ship.get_pos() };
				Laser_beam* x = new Laser_beam{ shot.first,shot.second,sz };
				lasers.push_back(x);
				lasers[lasers.size() - 1]->draw();
				lcd = 1;
			}
			break;
		}
	}
	return ret;
}
void MB_Invaders::view_highscores() {
	g_game_active = false;
	if (g_hs) delete g_hs;
	g_hs = new Highscores{ 50, 50, 1200, 850,"Highscores" };
}
void MB_Invaders::reset() {
	g_score = 0;
	g_game_active = true;
	g_game_restart = false;
	g_name = "unknown";

	hostile_time = 2;
	hostile_moving_speed = 1;

	for (unsigned int i = 0; i < lasers.size(); ++i) {
		Laser_beam* x = lasers[i];
		delete x;
	}
	lasers.clear();

	for (unsigned int i = 0; i < hostiles.size(); ++i) {
		hostiles[i]->reset_pos();
		hostiles[i]->hide();
	}

	for (unsigned int i = 0; i < barriers.size(); ++i)barriers[i]->restore();
	g_d_coords = g_d_coords_backup;
}

int main() {
	srand((unsigned int)time(0));
	MB_Invaders win(50, 50, 1200, 800, 50, "Mettbrötchen Invaders");
	Start_window sw{ 50, 50, 1200, 830 };

	return Fl::run();
}