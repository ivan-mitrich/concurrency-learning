#pragma once
#include "Field.h"
#include "Fruit.h"
#include "Snake.h"

/*
* Main gameplay class.
* It is responsible for redrawing the console window,
* checking snake collisions and handling basic player input.
*
* Gameplay:
* player controls the snake object and tries to eat as many fruits as he can.
* Game is over when snake intersects its tail.
*/

class Game
{
private:
	Field field;
	Snake snake;
	
	/* There is only one fruit at the field */
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
	
	/* Called each loop iteration to redraw screen */
	void redraw_screen();
	/* updates field 2d array of char symbols */
	void update_field();
	
	/* consists of calling of each check collision functions. Called each loop iteration */
	void check_collisions();
	void check_snake_border_collision();
	void check_snake_fruit_collision();
	void check_snake_snake_collision();

	/* prints amount of eaten fruits when game is over */
	void print_score();

	
	void process_user_input();
	
	/* called in separate thread and calls process_user_input() member function*/
	void user_input_loop();
};

