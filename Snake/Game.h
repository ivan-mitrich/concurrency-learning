#pragma once
#include "Field.h"
#include "Fruit.h"
#include "Snake.h"

/*
* Main gameplay class.
* It is responsible for redrawing the console window,
* checking snake collisions and handling basic player input.
*/

class Game
{
private:
	Field field;
	Snake snake;
	Fruit fruit;

	bool game_over;
	bool fruit_eaten;
	
	/* Number of fruits eaten by the snake */
	int score;
public:
	Game();
	
	/* General function that invokes all other functions needed for game */
	void start_game();
	
private:
	/* Called in the beginning of the game and prints control keys to help player figure out how to play */
	void display_help();
	
	
	void redraw_screen();
	void update_field();
	
	void check_collisions();
	void check_snake_border_collision();
	void check_snake_fruit_collision();
	void check_snake_snake_collision();

	void print_score();

	void process_user_input();
	void user_input_loop();
};

