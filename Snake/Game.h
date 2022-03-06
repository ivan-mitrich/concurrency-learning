#pragma once
#include "Field.h"
#include "Fruit.h"
#include "Snake.h"

class Game
{
private:
	Field field;
	Snake snake;
	Fruit fruit;

	bool game_over;
	bool fruit_eaten;
public:
	Game();
	void start_game();

private:
	void redraw_screen();
	void update_field();
	void check_collisions();

	void check_snake_border_collision();
	void check_snake_fruit_collision();
};

