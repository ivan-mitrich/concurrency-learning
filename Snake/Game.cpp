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
		redraw_screen();
	}
}

void Game::redraw_screen()
{
	std::system("cls");
	if (fruit_eaten)
	{
		field.set_fruit_coordinates(fruit);
		fruit_eaten = false;
	}
	
	field.set_snake_coordinates(snake);
	auto field_symbols = field.get_field();
	for (const auto& row : field_symbols)
	{
		for (const auto& symbol : row)
			std::cout << symbol;
		std::cout << "\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
