#include "Game.h"
#include <cstdlib>
#include <thread>
Game::Game() : game_over(false), fruit_eaten(true)
{
	snake.set_initial_head_position(field.get_width() / 2 - 1, field.get_height() / 2 - 1);
}

void Game::start_game()
{
	while (!game_over)
	{
		snake.process_input();
		redraw_screen();
		
	}
}

void Game::redraw_screen()
{
	std::system("cls");
		
	check_collisions();
	update_field();

	auto field_symbols = field.get_field();	
	for (const auto& row : field_symbols)
	{
		for (const auto& symbol : row)
			std::cout << symbol;
		std::cout << "\n";
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void Game::update_field()
{
	field.update_inner_region();
	if (fruit_eaten)
	{
		fruit.recalculate_coordinates(field.get_width() - 1, field.get_height() - 1);
		fruit_eaten = false;
	}
	field.set_fruit_coordinates(fruit);
	field.set_snake_coordinates(snake);
}

void Game::check_collisions()
{
	check_snake_border_collision();

}

void Game::check_snake_border_collision()
{
	int snake_x = snake.get_head_x();
	int snake_y = snake.get_head_y();
	int field_height = field.get_height() - 1;
	int field_width = field.get_width() - 1;

	if (snake_x == 0)
	{
		snake.reset_head_x(field_width - 1);
	}
	else if (snake_x == field_width)
	{
		snake.reset_head_x(1);
	}

	if (snake_y == 0)
	{
		snake.reset_head_y(field_height - 1);
	}
	else if (snake_y == field_width)
	{
		snake.reset_head_y(1);
	}

}
