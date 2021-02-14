#include<FL/Fl_Window.h>
#include <FL/Fl_Output.H>

#include"Spaceship.h"
#include"Backrounds.h"
#include"Hostiles.h"

//to do:
//Highscore Window, resume button
//Game Over window: shows score, lets you enter your name, restart the game or quit
//Button to view highscores

class MB_Invaders :public Fl_Window {

	bool game_active = true;			//turns false when a hostile reaches a position where it cant be killed anymore. stops the game.
							
	double time = 0.25;					//timespan for reoccuring events
	double hostile_time = 2;			//timespan for adding new rows of hostiles(will be increased to 8 after first run)
	double hostile_moving_speed = 1;
	
	int hostile_space = 120;			//distance between hostiles( gets incresed and reseted)
	int hostile_movement = 1;			//handles hostile moving pattern, gets increased and reseted
	int hostile_row_start = 0;			//iterating value for hostiles
	int hostile_row_end = 10;			//iterating value for hostiles

	int x;								
	int y;
	int length;
	int sz;								//handles size of things

	Backround_lv1 backround;
	Spaceship ship;
	Score_panel score;

	std::vector<Laser_beam*>lasers;		//contains shots
	std::vector<Hostile*>hostiles;
public:
	
	MB_Invaders(int a, int b, int l, int h, int s, const char* title) : Fl_Window(a,b,l, h, title), x(a), y(b), length(l), sz(s),
		ship(525, 650, sz),
		backround(x, y, l / 12 * 11 + 2, h),score(length-95,y+20)
	{	
		position(x, y);						//Window-Position
		size_range(l, h, l, h);				//locks Window-Size

		hostiles.reserve(150);
		for (unsigned int i = 0; i < 150; ++i) {		//for some reason, Hostiles have to be created inside the constructor
			Hostile* x = new Hostile{ hostile_space ,100  };
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
		show();
	}
	~MB_Invaders() {}

	static void move_lasers(void* addr) {

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->time, move_lasers, addr);
		if (mbiw->game_active) {
			for (unsigned int i = 0; i < mbiw->lasers.size(); ++i) {
				mbiw->lasers[i]->move(-10);							//projectile moves
				if (mbiw->lasers[i]->get_pos().second <= 0) {			//projectile gets deleted when it reaches the top
					Laser_beam* x = mbiw->lasers[i];
					delete x;
					mbiw->lasers.erase(mbiw->lasers.begin() + i);
					mbiw->lasers.shrink_to_fit();
				}
			}
		}
	}
	static void add_hostiles(void* addr) {						//actually just makes hostiles visible and active

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->hostile_time, add_hostiles, addr);

		if (mbiw->game_active) {

			for (; mbiw->hostile_row_start < mbiw->hostile_row_end; ++mbiw->hostile_row_start)
				mbiw->hostiles[mbiw->hostile_row_start]->show();

			mbiw->hostile_row_end += 10;

			if (mbiw->hostile_row_start >= 150) {
				mbiw->hostile_row_start = 0;
				mbiw->hostile_row_end = 10;
			}

			if (mbiw->hostile_time == 2)mbiw->hostile_time = 8;
		}
	}
	static void move_hostiles(void* addr) {

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->hostile_moving_speed, move_hostiles, addr);

		if (mbiw->game_active) {

			if (mbiw->hostile_movement > 8)mbiw->hostile_movement = 1;

			for (unsigned int i = 0; i < mbiw->hostiles.size(); ++i) {
				if (mbiw->hostiles[i]->active() && mbiw->hostile_movement < 4)mbiw->hostiles[i]->move(20, 0);
				if (mbiw->hostiles[i]->active() && mbiw->hostile_movement == 4)mbiw->hostiles[i]->move(0, 50);
				if (mbiw->hostiles[i]->active() && mbiw->hostile_movement > 4 && mbiw->hostile_movement < 8)mbiw->hostiles[i]->move(-20, 0);
				if (mbiw->hostiles[i]->active() && mbiw->hostile_movement == 8)mbiw->hostiles[i]->move(0, 50);
				if (mbiw->hostiles[i]->get_y() > 650)mbiw->game_active = false;
			}
			++mbiw->hostile_movement;

		}
	}
	static void kill_hostiles(void* addr) {					//this is where hostiles and laser-projectiles get deleted/hidden in case of a hit

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->time, kill_hostiles, addr);
		if (mbiw->game_active) {
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
							mbiw->score.add_score();
						}
					}
				}
			}
		}
	}
	static void speed_up(void* addr) {					//increases speed of hostiles depending on the score

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->time, speed_up, addr);


		int curr_sore = mbiw->score.get_score();
		if (curr_sore > 150) {
			mbiw->hostile_moving_speed = 0.75;
			mbiw->hostile_time = 6;
		}
		if (curr_sore > 300) {
			mbiw->hostile_moving_speed = 0.5;
			mbiw->hostile_time = 4;
		}
		if (curr_sore > 600) {
			mbiw->hostile_moving_speed = 0.25;
			mbiw->hostile_time = 2.1;
		}
	}
	void reset() {
		game_active = true;
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
		score.reset_score();
	}
	int handle(int event) {							//fltk handle for keyboard input
		int ret = Fl_Window::handle(event);			//used as return value

		if (game_active) {

			switch (event) {
			case FL_FOCUS:
			case FL_UNFOCUS:
				break;									//apparently this break is important
			case FL_SHORTCUT:
			case FL_KEYDOWN:
				break;
			case FL_KEYUP:
				printf("%d%c",Fl::event_key(),'\n');	//for debug-purpose, gets key-value

				if (Fl::event_key() == 97 || Fl::event_key() == 65361)if (ship.get_pos().first > x - 25)ship.move(-10);				//move to the left
				if (Fl::event_key() == 100 || Fl::event_key() == 65363)if (ship.get_pos().first < length / 12 * 11 - 25)ship.move(10);	//move to the right

				if (Fl::event_key() == 32) {			//shots been fired

					std::pair<int, int>shot{ ship.get_pos() };
					Laser_beam* x = new Laser_beam{ shot.first,shot.second,sz };
					lasers.emplace_back(x);
					lasers[lasers.size() - 1]->draw();
				}
			}
		}
		return (ret);
	}
};


int main() {
	srand((unsigned int)time(0));

	MB_Invaders win(50, 50, 1200, 800, 50,"Mettbrötchen Invaders");


	return Fl::run();

}