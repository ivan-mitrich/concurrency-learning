#pragma once
#include<vector>

struct ObstacleSpawnerSettings {
	int min_x = 0;
	int max_x = 1;

	int road_length = 1;

	int min_speed = 1;
	int max_speed = 1;

	int min_size = 3;
	int max_size = 3;

	std::vector<char> symbols = {'v'};
};

class RoadObject;

class ObstaclesSpawner
{
private:
	ObstacleSpawnerSettings settings;

	std::vector<RoadObject*> obstacles;

public:
	ObstaclesSpawner(int minimum_x = 0, int maximum_x = 0);

	void spawn_obstacle();
	const std::vector<RoadObject*>& get_obstacles() const { return obstacles; }

	void remove_obstacle(RoadObject* obstacle);

	void set_spawning_x_range(int min, int max);
	void set_road_length(int length);
	void set_obstacles_size_range(int min, int max);
	void set_obstacles_speed_range(int min, int max);
	void set_obstacles_symbols(const std::vector<char>& symbols);
private:
	static int get_random_int_in_range(int min, int max);
	char get_obstacle_symbol();
	bool is_x_position_possible(int new_object_x, int new_object_width, int new_obstacle_speed);
};

