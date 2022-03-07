#include "Snake.h"
#include <conio.h>

Snake::Snake()
{
	body.resize(1);
	body[0].symbol = 'O';
}

void Snake::set_initial_head_position(int i, int j)
{
	body[0].x = i;
	body[0].y = j;
}

void Snake::add_link()
{
	Link new_link(previous_tail_x, previous_tail_y, 'o');
	body.push_back(new_link);
}

void Snake::process_input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			update_tail_position();
			move_left();
			break;
		case 'd':
			update_tail_position();
			move_right();
			break;
		case 'w':
			update_tail_position();
			move_top();
			break;
		case 's':
			update_tail_position();
			move_bottom();
			break;
		}		
	}
}

void Snake::reset_head_x(int new_x)
{
	body[0].x = new_x;
}

void Snake::reset_head_y(int new_y)
{
	body[0].y = new_y;
}

void Snake::save_previous_tail_position()
{
	previous_tail_x = body[body.size() - 1].x;
	previous_tail_y = body[body.size() - 1].y;
}

void Snake::update_tail_position()
{
	save_previous_tail_position();
	for (std::size_t i = body.size() - 1; i > 0; --i)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
}
