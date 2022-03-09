#include "ObstaclesSpawner.h"
#include "RoadObject.h"
#include <random>

ObstaclesSpawner::ObstaclesSpawner(int minimum_x, int maximum_x) : min_x(minimum_x), max_x(maximum_x)
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
		while (!obstacle)
		{
			int y_position = 0;
			int x_position = get_random_int_in_range(min_x, max_x);
			if (is_x_position_possible(x_position, NEW_OBSTACLE_WIDTH))
			{
				obstacle = new RoadObject;
				obstacles.push_back(obstacle);
			}
		}
	}
}

int ObstaclesSpawner::get_random_int_in_range(int min, int max)
{
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distribution(min, max);
	return distribution(generator);
}

bool ObstaclesSpawner::is_x_position_possible(int new_object_x, int new_object_width)
{
	for (const auto& obstacle : obstacles)
	{
		int distance = 0;
		if (new_object_x < obstacle->get_x_position())
		{
			distance = std::fabs(obstacle->get_x_position() + obstacle->get_width() - new_object_x);
		}
		else
		{
			distance = std::fabs(new_object_x + new_object_width - obstacle->get_x_position());
		}

		if (distance < new_object_width + obstacle->get_x_position())
		{
			return false;
		}			
	}
	return true;
}
