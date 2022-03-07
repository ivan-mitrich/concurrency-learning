#include "Game.h"
#include <cstdlib>
#include <thread>
#include <Windows.h>

Game::Game() : game_over(false), fruit_eaten(true), score(0)
{
	snake.set_initial_head_position(field.get_width() / 2 - 1, field.get_height() / 2 - 1);
}

void Game::start_game()
{
	display_help();

	std::thread user_input_thread(&Game::user_input_loop, this);
	
	while (!game_over)
	{
		snake.move_snake();
		redraw_screen();
	}

	user_input_thread.join();

	print_score();
}

void Game::redraw_screen()
{
	const int HELP_ROWS_AMOUNT = 9;
	COORD cur = { 0, HELP_ROWS_AMOUNT };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
		
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
	check_snake_fruit_collision();
	check_snake_snake_collision();
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

void Game::check_snake_fruit_collision()
{
	int fruit_x = fruit.get_x();
	int fruit_y = fruit.get_y();
	int snake_x = snake.get_head_x();
	int snake_y = snake.get_head_y();

	if (snake_x == fruit_x && snake_y == fruit_y)
	{
		fruit_eaten = true;
		snake.add_link();
		++score;
	}
}

void Game::check_snake_snake_collision()
{
	auto snake_body = snake.get_body();
	for (size_t i = 0; i < snake_body.size()-1; ++i)
	{
		for (size_t j = i + 1; j < snake_body.size(); ++j)
		{
			if (snake_body[i].x == snake_body[j].x && snake_body[i].y == snake_body[j].y)
			{
				game_over = true;
				return;
			}
		}
	}
}

void Game::print_score()
{
	std::cout << "GAME OVER" << std::endl;
	std::cout << "Your score : " << score << std::endl;
}

void Game::process_user_input()
{
	if (_kbhit())
	{
		int key = _getch();
		switch (key)
		{
		case 'p':
			snake.pause_moving();
			break;
		case 'c':
			snake.continue_moving();
			break;
		case 'x':
			game_over = true;
			break;
		default:
			snake.process_input(key);
			break;
		}
	}
	
}

void Game::user_input_loop()
{
	while (!game_over)
	{
		process_user_input();
	}
}

void Game::display_help()
{
	std::cout << "============ SNAKE GAME ============" << "\n";
	std::cout << "  Keyboard input: " << "\n";
	std::cout << "     *w,a,s,d - move snake;" << "\n";
	std::cout << "     *p - pause game;" << "\n";
	std::cout << "     *c - continue game;" << "\n";
	std::cout << "     *x - exit game;" << "\n";
	std::cout << "  Tip: don't let snake eat itself!" << "\n";
	std::cout << "============ Good Luck! ============" << "\n";
}