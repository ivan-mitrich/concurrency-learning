#include "ObstaclesSpawner.h"
#include "RoadObject.h"
#include <random>

ObstaclesSpawner::ObstaclesSpawner(int minimum_x, int maximum_x) : min_x(minimum_x), max_x(maximum_x)
{

}

void ObstaclesSpawner::spawn_obstacle()
{
	int is_spawning_allowed = get_random_int_in_range(0, 1);
	if (is_spawning_allowed) 
	{
		RoadObject* obstacle = nullptr;
		while (!obstacle)
		{
			int y_position = 0;
			int x_position = get_random_int_in_range(min_x, max_x);
			if (is_x_position_possible(x_position))
			{
				obstacle = new RoadObject;
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

bool ObstaclesSpawner::is_x_position_possible(int x)
{
	for (const auto& obstacle : obstacles)
	{
		if(x > obstacle->get_x_position() + obstacle->get_width() )
	}
	return true;
}
