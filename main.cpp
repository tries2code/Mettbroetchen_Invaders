#include<thread>

#include<FL/Fl_Window.h>
#include<FL/Fl_Button.H>

#include"Spaceship.h"
#include"Backrounds.h"
#include"Hostiles.h"



class MB_Invaders :public Fl_Window {
							
	double time = 0.25;				//timespan for reoccuring events
	double hostile_time = 2;			//timespan for adding new rows of hostiles(will be increased to 8 after first run)

	int hostile_space = 50;				//distance between hostiles( gets incresed and reseted)
	int hostile_movement = 0;			//handles hostile moving pattern, gets increased and reseted
	int hostile_row_start = 0;			//iterating value for hostiles
	int hostile_row_end = 10;			//iterating value for hostiles


	int x;								
	int y;
	int length;
	int sz;								//handles size of things

	Backround_lv1 br1;
	Spaceship ship;
	std::vector<Laser_beam*>lasers;		//contains shots
	std::vector<Hostile*>hostiles;

public:
	MB_Invaders(int a, int b, int l, int h, int s,const char* title): Fl_Window(l, h, title), x(a), y(b),length(l), sz(s),
		ship(525,650,sz),
		br1(x,y,l/12*11+2,h)
	{	
		position(x, y);						//Window-Position
		size_range(l, h, l, h);				//locks Window-Size

		hostiles.reserve(150);
		for (unsigned int i = 0; i < 150; ++i) {		//for some reason, Hostiles have to be created inside the constructor
			Hostile* x = new Hostile{ hostile_space ,100  };
			hostiles.push_back(x);
			hostiles[hostiles.size() - 1]->hide();
			hostile_space += 100;

			if (hostile_space == 950) {
				hostile_space = 50;
			}
		}

		Fl::add_timeout(time, move_lasers, (void*)this);
		Fl::add_timeout(hostile_time, add_hostiles, (void*)this);	//actually just makes hostiles visible and active
		Fl::add_timeout(1, move_hostiles, (void*)this);				//moves only active hostiles

		show();
	}
	~MB_Invaders() {}

	static void move_lasers(void* addr) {

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->time, move_lasers, addr);
		
		for (unsigned int i = 0; i < mbiw->lasers.size(); ++i) {
			mbiw->lasers[i]->move(0, -10);							//projectile moves
		
			if (mbiw->lasers[i]->get_pos().second <= 0) {			//projectile gets deleted when it reaches the top
  				Laser_beam* x = mbiw->lasers[i];
				delete x;
				mbiw->lasers.erase(mbiw->lasers.begin() + i);
				mbiw->lasers.shrink_to_fit();
			}
		}
	}
	static void add_hostiles(void* addr) {						//actually just makes hostiles visible and active

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(mbiw->hostile_time, add_hostiles, addr);
		for (; mbiw->hostile_row_start < mbiw->hostile_row_end; ++mbiw->hostile_row_start)
			mbiw->hostiles[mbiw->hostile_row_start]->show();

		mbiw->hostile_row_end += 10;

		if (mbiw->hostile_row_start >= 150) {
			mbiw->hostile_row_start = 0;
			mbiw->hostile_row_end = 10;
		}

		if (mbiw->hostile_time !=8)mbiw->hostile_time = 8;
	}
	static void move_hostiles(void* addr) {

		MB_Invaders* mbiw = (MB_Invaders*)addr;
		Fl::add_timeout(1, move_hostiles, addr);

		++mbiw->hostile_movement;
		if (mbiw->hostile_movement > 8)mbiw->hostile_movement = 0;

		for (unsigned int i = 0; i < mbiw->hostiles.size(); ++i) {
			if(mbiw->hostiles[i]->active()&&mbiw->hostile_movement<4)mbiw->hostiles[i]->move(20, 0);
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement == 4)mbiw->hostiles[i]->move(0, 50);
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement > 4 && mbiw->hostile_movement < 8)mbiw->hostiles[i]->move(-20, 0);
			if (mbiw->hostiles[i]->active() && mbiw->hostile_movement == 8)mbiw->hostiles[i]->move(0, 50);
		}
	}
	
	int handle(int event) {
		int ret = Fl_Window::handle(event);			//Wird als return-Wert benutzt. return 0 geht aber auch...
		
		switch (event) {
		case FL_FOCUS:
		case FL_UNFOCUS:
			//ret = 1;								//Müsste laut Dokumentation 1 wiedegeben um Keyboard-Events zu ermöglichen.Geht wohl auch ohne...
			break;
		case FL_SHORTCUT:
		case FL_KEYDOWN:
		case FL_KEYUP:
			//printf("%d%c",Fl::event_key(),'\n');	//Druckt Keyboard-Tasten-Nummern. Man kann auch den Text drucken mit Fl::event_text()

			if (Fl::event_key() == 97 || Fl::event_key() == 65361)if(ship.get_pos().first>x-25)ship.move(-25, 0);				//Bewegung nach links
			if (Fl::event_key() == 100 || Fl::event_key() == 65363)if (ship.get_pos().first<length/12*11-25)ship.move(25, 0);	//Bewegung nach rechts
			//if (Fl::event_key() == 119 || Fl::event_key() == 65362)ship.move(0, -25);		//Bewegung nach oben
			//if (Fl::event_key() == 115 || Fl::event_key() == 65364)ship.move(0, 25);		//Bewegung nach unten

			if (Fl::event_key() == 32) {			//Hier wird geschossen

				std::pair<int, int>shot{ ship.get_pos() };
				Laser_beam* x = new Laser_beam{ shot.first,shot.second,sz };
				lasers.emplace_back(x);
				lasers[lasers.size() - 1]->draw();
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