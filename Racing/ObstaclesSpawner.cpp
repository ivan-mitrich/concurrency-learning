#include "ObstaclesSpawner.h"
#include "RoadObject.h"
#include <random>
#include <iostream>
ObstaclesSpawner::ObstaclesSpawner(int minimum_x, int maximum_x)
{
	const int APPROXIMATE_OBSTACLES_AMOUNT = 10;
	obstacles.reserve(APPROXIMATE_OBSTACLES_AMOUNT);



}

void ObstaclesSpawner::spawn_obstacle()
{
	int is_spawning_allowed = get_random_int_in_range(0, 1);
	if (is_spawning_allowed) 
	{
		RoadObject* obstacle = nullptr;
		const int NEW_OBSTACLE_WIDTH = 4;
		
		int obstacle_size = get_random_int_in_range(settings.min_size, settings.max_size);
		int x_position = get_random_int_in_range(settings.min_x, settings.max_x - obstacle_size);
		
		if (is_x_position_possible(x_position, NEW_OBSTACLE_WIDTH))
		{
			int obstacle_speed = get_random_int_in_range(settings.min_speed, settings.max_speed);
			char symbol = get_obstacle_symbol();
			obstacle = new RoadObject(obstacle_size, obstacle_size, obstacle_speed, symbol);
			obstacle->set_x_position(x_position);
			obstacles.push_back(obstacle);
		}
	}
}

void ObstaclesSpawner::set_spawning_x_range(int min, int max)
{
	settings.min_x = min;
	settings.max_x = max;
}

void ObstaclesSpawner::set_obstacles_size_range(int min, int max)
{
	settings.min_size = min;
	settings.max_size = max;
}

void ObstaclesSpawner::set_obstacles_speed_range(int min, int max)
{
	settings.min_speed = min;
	settings.max_speed = max;
}

void ObstaclesSpawner::set_obstacles_symbols(const std::vector<char>& symbols)
{
	if (!symbols.empty())
	{
		settings.symbols = symbols;
	}
}


int ObstaclesSpawner::get_random_int_in_range(int min, int max)
{
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distribution(min, max);
	return distribution(generator);
}

char ObstaclesSpawner::get_obstacle_symbol()
{
	int min_index = 0;
	int max_index = settings.symbols.size() - 1;
	
	int random_index = get_random_int_in_range(min_index, max_index);
	
	return settings.symbols[random_index];
}

bool ObstaclesSpawner::is_x_position_possible(int new_object_x, int new_object_width)
{
	for (const auto& obstacle : obstacles)
	{
		if (obstacle->get_y_position() <= 0)
		{
			return false;
		}
		else if (obstacle->get_y_position() > obstacle->get_height())
		{
			continue;
		}


		int distance = 0;
		if (new_object_x < obstacle->get_x_position())
		{
			distance = std::abs(obstacle->get_x_position() + obstacle->get_width() - new_object_x);
		}
		else
		{
			distance = std::abs(new_object_x + new_object_width - obstacle->get_x_position());
		}

		if (distance < new_object_width + obstacle->get_width())
		{
			return false;
		}		

	}
	return true;
}
