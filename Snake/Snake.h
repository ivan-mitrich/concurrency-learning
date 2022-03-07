#pragma once
#include <vector>
#include <conio.h>

enum class Direction {
	STOP,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

struct Link {
	Link(int i = 1, int j = 1, char c = 'o') : x(i), y(j), symbol(c) {}
	
	int x;
	int y;
	char symbol;
};

class Snake
{
private:
	std::vector<Link> body;

	int previous_tail_x;
	int previous_tail_y;

	Direction move_direction;
	Direction saved_move_direction;
public:
	Snake();

	void reset_head_x(int new_x);
	void reset_head_y(int new_y);

	void process_input();
	void set_initial_head_position(int i, int j);
	void add_link();
	const std::vector<Link>& get_body() const { return body; }
	
	int get_head_x() const { return body[0].x; }
	int get_head_y() const { return body[0].y; }

	void stop_moving();
	void continue_moving();

private:
	void move_left() { --body[0].x; }
	void move_right() { ++body[0].x; }
	
	//move top uses decrement operator since field (0; 0)-point is located in top left corner 
	//and to move top one needs to decrement coordinate
	//the same with move bottom.
	void move_top() { --body[0].y; } 
	void move_bottom() { ++body[0].y; }

	void move_snake();

	void update_tail_position();
	void save_previous_tail_position();
};

