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