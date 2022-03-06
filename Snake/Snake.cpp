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
	Link tail = body[body.size() - 1];
	Link new_link(tail.x, tail.y, 'o');
	body.push_back(new_link);
}

void Snake::process_input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			move_left();
			break;
		case 'd':
			move_right();
			break;
		case 'w':
			move_top();
			break;
		case 's':
			move_bottom();
			break;
		}
		update_tail_position();
	}
}

void Snake::update_tail_position()
{
	for (std::size_t i = 1; i < body.size(); ++i)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
}
