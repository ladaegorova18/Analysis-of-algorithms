#pragma once
#define ROUNDS 10
#define FILENAME "progress.txt"
#define START_BUSHELS 2800
#define START_POPULATION 100
#define START_ACRES 1000

struct Progress
{
	// start parameters
	int population = 100;
	int acres = 1000;
	float bushels = 2800;
	short year = 1;
	// -----------------

	// game statistics
	float P = 0.0;
	float L = 0.0;
	// -----------------
};

class City
{
public:
	City() {}
	void run_game();
private:

	// start parameters
	int population = 100;
	int acres = 1000;
	float bushels = 2800;
	short year = 0;
	// -----------------
	
	// hidden parameters
	float seed_per_acre = 0.5;
	int citizen_acre = 10;
	short portion = 20;
	// -----------------

	short acre_price = 0;

	int dead = 0;
	int arrived = 0;

	bool plague = false;

	// rats variables
	float max_rat_damage = 0.07;
	float rats_damage = 0.0;
	// -----------------

	int bushel_harvest = 0;
	short harvest_per_acre = 1;

	// player input 
	int acres_to_buy = 0;
	int acres_to_cell = 0;
	int bushels_to_eat = 0;
	int cultivated_acres = 0;
	// -----------------

	// game statistics
	float P = 0.0;
	float L = 0.0;
	// -----------------

	void print_round_statistics();
	void player_input();
	void check_input(int input);
	void input_warning();

	void trade_acres();
	void count_harvest();
	void count_rats_damage();
	void count_population_deaths();
	void count_arrived();
	void check_plague();

	void one_year();

	void count_statistics();
	void print_result();
	void game_over();

	void save_to_file();
	void read_from_file();
	void runner();
	void input_to_save();
	void restart();
};

