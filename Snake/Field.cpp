#include "Field.h"
#include "Fruit.h"
#include "Snake.h"

Field::Field(int h, int w, char border) : height(h), width(w), border_symbol(border)
{
	field.resize(height);
	for (auto& row : field)
		row.resize(width, ' ');
	set_horizontal_borders();
	set_vertical_borders();
}

void Field::set_fruit_coordinates(Fruit& fruit)
{
	field[fruit.get_x()][fruit.get_y()] = fruit.get_symbol();
}

void Field::set_snake_coordinates(Snake& snake)
{
	std::vector<Link> snake_body = snake.get_body();
	for (const auto& link : snake_body)
		field[link.y][link.x] = link.symbol;
}

void Field::set_horizontal_borders()
{
	for (int i = 0; i < width; ++i)
	{
		field[i][0] = '#';
		field[i][height - 1] = '#';
	}
}

void Field::update_inner_region()
{
	for (int i = 1; i < width-1; ++i)
	{
		for (int j = 1; j < height-1; ++j)
		{
			field[i][j] = ' ';
		}
	}
}

void Field::set_vertical_borders()
{
	for (int j = 0; j < height; ++j)
	{
		field[0][j] = '#';
		field[width - 1][j] = '#';
	}
}
