#pragma once
#include "Field.h"
#include "Car.h"
#include "ObstaclesSpawner.h"

class Game
{
private:
	Field field;
	Car player_car;
	ObstaclesSpawner spawner;

	bool game_over;

	//int score;
public:
	Game();
	void start_game();
	void display_help();

private:
	void redraw_screen();
	void update_field();
	void check_collisions();

	void print_score();

	void process_user_input();
	void user_input_loop();
	void spawning_obstacles_loop();

	void move_obstacles();
	void draw_obstacles();
};

