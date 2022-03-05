#include "Snake.h"

Snake::Snake()
{
	body.resize(1);
	body[0].symbol = 'O';
}

void Snake::add_link()
{
	Link tail = body[body.size() - 1];
	Link new_link(tail.x, tail.y, 'o');
	body.push_back(new_link);
}
