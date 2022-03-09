#pragma once
#include<vector>

class RoadObject;

class ObstaclesSpawner
{
private:
	int min_x;
	int max_x;

	std::vector<RoadObject*> obstacles;

public:
	ObstaclesSpawner(int minimum_x = 0, int maximum_x = 0);

	void spawn_obstacle();
	const std::vector<RoadObject*>& get_obstacles() const { return obstacles; }

private:
	static int get_random_int_in_range(int min, int max);
	bool is_x_position_possible(int x);
};

