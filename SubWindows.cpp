#include"SubWindows.h"

extern int g_score;
extern bool g_game_active;
extern bool g_game_restart;
extern std::string g_name;

Record::Record(int a, int b,int ff,int fs, std::string n) :Fl_Widget(a, b, a, b), 
x(a), y(b),font_face(ff),font_size(fs), name(n){}
void Record::draw() {
	fl_color(fc);
	fl_font(font_face, font_size);
	fl_draw(name.c_str(), x, y);
}
void Record::set_color(Fl_Color c) {
	fc = c;
}


Start_window::Start_window(int a, int b, int w, int h) :Fl_Window(a, b-30, w, h),
x(a), y(b), width(w), backround(a, b, w, h),
start(470, 500, 280, 60, "Start Game")
{			
	g_game_active = false;
	
	start.callback(cb_start, this);
	start.labelsize(40);
	start.labelfont(5);
	start.labelcolor(fc);
	start.box(FL_PLASTIC_UP_FRAME);
	start.color(FL_DARK_BLUE);

	title.set_color(fc);
	instr1.set_color(fc); 
	instr2.set_color(fc);
	instr3.set_color(fc);

	clear_border();										//Prevents closing the window by control bar which wont make the game start
	show();
}
void Start_window::start_game() {
	g_game_active = true;
	this->hide();
}


Highscores::Highscores(int a, int b, int w, int h, const char* title) :Fl_Window(a, b, w, h, title),
x(a), y(b), width(w), backround(a, b, w, h),
cont(430, 700, 280, 60, "Continue")
{														//the constructor loads data from the textfile and draws it on the screen
	cont.callback(cb_cont, this);
	cont.labelsize(40);
	cont.labelfont(5);
	cont.labelcolor(fc);
	cont.box(FL_PLASTIC_UP_FRAME);
	cont.color(FL_DARK_BLUE);

	hs_title.set_color(fc);

	std::vector<std::string>data;
	std::ifstream ifs{ "Highscores.txt" };
	std::string name;
	int score = 0;
	int place = 1;
	while (ifs) {
		ifs >> name >> score;
		std::stringstream ss;
		int range = 45 - name.length();
		ss <<place<<". "<< name << std::setw(range) << std::setfill('.') << score; //range takes care of having each record of same line-length
		data.push_back(ss.str());
		++place;
	}
	for (unsigned int i = 0; i < 10; ++i) {
		std::string table = data[i];
		if(i==9){ 
			Record* r = new Record{ x + 250,y + 150 + (50 * (int)i),5,19,table.c_str() }; 
			r->set_color(fc);
		}
		else {
			Record* r = new Record{ x + 260,y + 150 + (50 * (int)i),5,19,table.c_str() };
			r->set_color(fc);
		}
	}

	clear_border();										//Prevents closing the window by control bar which wont make the game continue
	show();
}
void Highscores::continue_game() {
	g_game_active = true; 
	this->hide();
}


Game_Over::Game_Over(int a, int b, int w, int h, const char* title) :Fl_Window(a, b, w, h),
x(a), y(b), width(w), backround(a, b, w, h),
cont( 300,500,250,60,"Continue" ),
quit( 625,500,200,60,"Quit" ),
enter_name( 565,400,210,30,"Enter your name" )
{
	cont.callback(cb_cont, this);
	cont.labelsize(40);
	cont.labelfont(5);
	cont.labelcolor(fc);
	cont.box(FL_PLASTIC_UP_FRAME);
	cont.color(FL_DARK_BLUE);

	quit.callback(cb_quit, this);
	quit.labelsize(40);
	quit.labelfont(5);
	quit.labelcolor(fc);
	quit.box(FL_PLASTIC_UP_FRAME);
	quit.color(FL_DARK_BLUE);

	enter_name.labelsize(40);
	enter_name.labelfont(5);
	enter_name.labelcolor(fc);

	go_title.set_color(fc);

	Record* r1 = new Record{ 200,325,5,60,"Your Score" };
	r1->set_color(fc);
	char points[50];
	sprintf(points, "%d", g_score);
	Record* r3 = new Record{ 730,325,5,90,points };
	r3->set_color(fc);

	clear_border();
	show();
}
void Game_Over::continue_game() {
	g_game_restart = true;
	save_score();
	this->hide();
}
void Game_Over::quit_game() {
	save_score();
	exit(0);
}
void Game_Over::save_score() {	//Loads existing data for txt file and adds current score and payer name, if the player score well enough to be in the Top 10
	std::vector<std::pair<int,std::string>>data;
	std::ifstream ifs{ "Highscores.txt" };
	std::string name;
	int score = 0;
	while (ifs) {
		ifs >> name >> score;
		data.emplace_back(score,name);
	}
	g_name = enter_name.value();
	if (g_name.empty())g_name = "unknown";
	std::string table;
	for (unsigned int i = 0; i < g_name.size(); ++i) {
		if (isspace(g_name[i]))table += "_";
		else table += g_name[i];
		if (table.length() == 32)break;
	}
	g_name = table;
	data.emplace_back(g_score, g_name);
	sort(data.begin(), data.end());
	reverse(data.begin(), data.end());
	std::ofstream ofs{ "Highscores.txt" };
	for (int i = 0; i < 10; ++i) ofs << data[i].second << " " << data[i].first << '\n';
}