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
	int is_spawning_allowed = get_random_int_in_range(0, 3);
	if (is_spawning_allowed != 0) 
	{
		RoadObject* obstacle = nullptr;
		
		int obstacle_size = get_random_int_in_range(settings.min_size, settings.max_size);
		int x_position = get_random_int_in_range(settings.min_x, settings.max_x - obstacle_size);
		int obstacle_speed = get_random_int_in_range(settings.min_speed, settings.max_speed);

		if (is_x_position_possible(x_position, obstacle_size, obstacle_speed))
		{			
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

void ObstaclesSpawner::set_road_length(int length)
{
	settings.road_length = length;
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

bool ObstaclesSpawner::is_x_position_possible(int new_object_x, int new_object_size, int new_obstacle_speed)
{
	for (const auto& obstacle : obstacles)
	{
		int obstacle_y_coordinate = obstacle->get_y_position();
		if (obstacle_y_coordinate <= 0)
		{
			return false;
		}
		else 
		{
			float obstacles_speed_ratio = (float)new_obstacle_speed / (float)obstacle->get_speed();
			
			if( std::round(obstacles_speed_ratio) != 1.f )
			{ 			
				int y_distance = std::ceil(obstacles_speed_ratio * (settings.road_length - obstacle_y_coordinate));
				if (obstacle->get_y_position() > y_distance)
				{
					continue;
				}
			}
			else if (obstacle->get_y_position() > obstacle->get_height())
			{
				continue;
			}
		}


		int x_distance = 0;
		if (new_object_x < obstacle->get_x_position())
		{
			x_distance = std::abs(obstacle->get_x_position() + obstacle->get_width() - new_object_x);
		}
		else
		{
			x_distance = std::abs(new_object_x + new_object_size - obstacle->get_x_position());
		}

		if (x_distance < new_object_size + obstacle->get_width())
		{
			return false;
		}		

	}
	return true;
}
