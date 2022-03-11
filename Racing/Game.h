#pragma once
#include "Field.h"
#include "Car.h"
#include "ObstaclesSpawner.h"
#include "Timer.h"

class Game
{
private:
	Field field;
	Car player_car;
	ObstaclesSpawner spawner;
	Timer timer;

	bool paused;
	bool game_over;

public:
	Game();
	void start_game();
	void display_help();

private:
	void redraw_screen();
	void update_field();
	void check_collisions();

	void check_car_obstacle_collision(const RoadObject const *object);
	bool has_dimension_intersection_between_objects(int object1_min, int object1_max, int object2_min, int object2_max, int sum_leght);

	void print_score();

	void process_user_input();
	void user_input_loop();

	void move_obstacles();
	void draw_obstacles();
};

