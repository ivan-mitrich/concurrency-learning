#include "Game.h"
#include <conio.h>
#include <thread>
#include <Windows.h>

Game::Game() : game_over(false)
{
	player_car.set_x_position(field.get_width() / 2);
	player_car.set_y_position(field.get_height() - player_car.get_height());

	spawner.set_spawning_x_range(1, field.get_width() - 2);
	spawner.set_obstacles_size_range(2, 3);
	spawner.set_obstacles_speed_range(1, 2);
	spawner.set_obstacles_symbols(std::vector<char>{'v', 'c', '$', '*', '9', '@', 'P'});
	spawner.set_road_length(field.get_height());
}

void Game::start_game()
{
	display_help();

	//std::thread user_input_thread(&Game::user_input_loop, this);
	//std::thread spawner_thread(&Game::spawning_obstacles_loop, this);
	
	while (!game_over)
	{
		process_user_input();
		spawner.spawn_obstacle();
		player_car.move();
		move_obstacles();
		redraw_screen();
	}

	//user_input_thread.join();
	//spawner_thread.join();

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
	field.update_road();
	field.set_car_on_field(player_car);
	draw_obstacles();
}

void Game::check_collisions()
{
	auto obstacles = spawner.get_obstacles();
	for (const auto& obstacle : obstacles)
	{
		check_car_obstacle_collision(obstacle);
	}
}

void Game::check_car_obstacle_collision(const RoadObject const* object)
{
	int obstacle_x_min = object->get_x_position();
	int obstacle_y_min = object->get_y_position();
	int obstacle_x_max = obstacle_x_min + object->get_width();
	int obstacle_y_max = obstacle_y_min + object->get_height();
	int car_x_min = player_car.get_x_position();
	int car_y_min = player_car.get_y_position();
	int car_x_max = car_x_min + player_car.get_width();
	int car_y_max = car_y_min + player_car.get_height();


	bool has_x_intersection = has_dimension_intersection_between_objects(car_x_min, car_x_max, obstacle_x_min, obstacle_x_max, player_car.get_width() + object->get_width());

	bool has_y_intersection = has_dimension_intersection_between_objects(car_y_min, car_y_max, obstacle_y_min, obstacle_y_max, player_car.get_height() + object->get_height());

	if (has_x_intersection && has_y_intersection)
	{
		game_over = true;
	}
}

bool Game::has_dimension_intersection_between_objects(int object1_min, int object1_max, int object2_min, int object2_max, int sum_leght)
{
	bool has_intersection = false;
	int distance = 0;
	if (object1_min < object2_min)
	{
		distance = object2_max - object1_min;
	}
	else
	{
		distance = object1_max - object2_min;
	}
	if (distance < sum_leght)
	{
		has_intersection = true;
	}
	return has_intersection;
}

void Game::print_score()
{
	std::cout << "GAME OVER" << std::endl;
	//std::cout << "Your score : " << score << std::endl;
}

void Game::process_user_input()
{
	if (_kbhit())
	{
		int key = _getch();
		switch (key)
		{
		case 'p':
			//snake.pause_moving();
			break;
		case 'c':
			//snake.continue_moving();
			break;
		case 'x':
			game_over = true;
			break;
		default:
			player_car.process_input(key);
			//snake.process_input(key);
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

void Game::spawning_obstacles_loop()
{
	while (!game_over)
	{
		spawner.spawn_obstacle();
	}
}

void Game::move_obstacles()
{
	auto obstacles = spawner.get_obstacles();
	for (const auto& obstacle : obstacles)
	{
		obstacle->move();
	}
}

void Game::draw_obstacles()
{
	auto obstacles = spawner.get_obstacles();
	
	for (const auto& obstacle : obstacles)
	{
		field.set_obstacle_on_field(*obstacle);
	}
}

void Game::display_help()
{
	std::cout << "============ RACING GAME ============" << "\n";
	std::cout << "  Keyboard input: " << "\n";
	std::cout << "     *w,a,s,d - move car;" << "\n";
	//std::cout << "     *p - pause game;" << "\n";
	//std::cout << "     *c - continue game;" << "\n";
	std::cout << "     *x - exit game;" << "\n";
	std::cout << "  Tip: follow the traffic rules!" << "\n";
	std::cout << "============ Good Luck! ============" << "\n";
}