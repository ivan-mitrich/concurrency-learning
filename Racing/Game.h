#pragma once
#include "Field.h"
#include "Car.h"
#include "ObstaclesSpawner.h"
#include "Timer.h"

/*
* Main class to handle gameplay events such as player input, objects moving, collisions ...
*
* Gameplay : 
* player controls the player_car created at the bottom of the screen when game starts.
* During the game player tries to avoid obstacles moving down from the top of the screen.
* These obstacles are spawned randomly at the top of the screen. They have different sizes and velocities.
*/

class Game
{
private:
	/* Represents playable area as 2D char array */
	Field field;

	/* Represents car controlled by player */
	Car player_car;

	/* Represents road obstacles spawner class */
	ObstaclesSpawner spawner;

	/* Represents wrapper of std::chrono::high_resolution_clock needed to record player time in the game */
	Timer timer;

	/* Represents condition if game is paused */
	bool paused;

	/* Represents condition if game is over */
	bool game_over;

public:
	Game();

	/* Called to launch game */
	void start_game();

private:

	/* Called before game is started to print info how to drive the car with keyboard */
	void display_help();
	
	/* Move all obstacles down the road*/
	void move_obstacles();

	/* Launch for each loop for each =) obstacle to check their collision with player car */
	void check_collisions();

	/* Call field update function and print field to console */
	void redraw_screen();

	/* Called every main game loop step to update field 2d array: place player car, obstacles and road marks in proper posions */
	void update_field();

	/* Called in update_field() function to put obstacles to field 2d array in correct position */
	void draw_obstacles();
	
	/* Called in check collisions function for each obstacle to check if it intersect the player car */
	void check_car_obstacle_collision(const RoadObject const *object);

	/* 
	*  Needed to calculate intersection between two objects in specific dimension (x or y) 
	*  object1_min - left or top field-coordinate of object1 depending on chosen dimension (x or y) where intersection are finding
	*  object1_max - object1_min + object1 size in chosen dimension
	*  object2_min - left or top field-coordinate of object2 depending on chosen dimension (x or y) where intersection are finding
	*  object2_min - object2_min + object2 size in chosen dimension
	*/
	bool has_dimension_intersection_between_objects(int object1_min, int object1_max, int object2_min, int object2_max, int sum_leght);

	/* Print played time when game is over */
	void print_score();

	/* Handle user input when he/she press the keyboard */
	void process_user_input();
	
	/* Function to launch process_user_input() in while loop in separate thread */
	void user_input_loop();

};

